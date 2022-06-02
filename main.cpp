#include <iostream>
#include "MoleculeBox.hpp"
#include "spdlog/sinks/basic_file_sink.h"
#include <hpx/init.hpp>
#include "include/hpx_box_component/communicator.hpp"
#include <hpx/future.hpp>
#include <hpx/iostream.hpp>
#include <span>
#include <algorithm>
#include <hpx/modules/collectives.hpp>


using namespace Geometry;
using namespace Domain;

typedef std::vector<Atom> communication_type;

HPX_REGISTER_CHANNEL(communication_type)

typedef communicator<communication_type> comm_type;

typedef hpx::future<std::vector<Atom>> future_vector;

int hpx_main(hpx::program_options::variables_map &vm) {
    auto my_rank = hpx::get_locality_id();
    auto num_ranks = hpx::get_num_localities().get();
    const Coordinate2D my_top_left = Coordinate2D{5.0 * my_rank, 0};
    const Coordinate2D my_bottom_right = Coordinate2D{5.0 * (my_rank + 1), 5.0};
    const Rectangle my_rectangle(my_top_left, my_bottom_right);
    const Coordinate2D global_top_left{0.0, 0.0};
    const Coordinate2D global_bottom_right{5.0 * num_ranks, 5.0};
    const Rectangle global_rect(global_top_left, global_bottom_right);
    communicator<communication_type> comms(my_rank, num_ranks);
    Atom atom1{Coordinate2D::random_coord(my_top_left, my_bottom_right), my_rank, Coordinate2D{1.0, 0}};
    Atom atom2{Coordinate2D::random_coord(my_top_left, my_bottom_right), my_rank, Coordinate2D{-1.0, 0}};

    auto logger = spdlog::basic_logger_mt("basic_logger", spdlog::fmt_lib::format("../basic-log{}.txt", my_rank));


    auto refit_to_box = [global_rect](future_vector future_atoms) -> communication_type {
        auto atoms = future_atoms.get();
        std::for_each(atoms.begin(), atoms.end(), [&global_rect](Atom &atom) -> Atom {
                          global_rect.refit_into_container(atom.position);
                          atom.move();
                          return atom;
                      }
        );
        return atoms;
    };

    MoleculeBox my_box(my_rectangle, {atom1, atom2});
    auto size_before_sim = hpx::collectives::all_reduce("number_of_atoms", my_box.atoms.size(),
                                                        [](auto left, auto right) {
                                                            return left + right;
                                                        }).get();

    logger->info("Before simulation wer had {} atoms", size_before_sim);

    auto left_send = comms.set(comm_type::LEFT, {}, 0);
    auto right_send = comms.set(comm_type::RIGHT, {}, 0);
    bool wait = true;


    communication_type left_buff;
    communication_type right_buff;

    logger->info("started with {}", spdlog::fmt_lib::join(my_box.atoms, "\n"));


    for (size_t i = 1; i < 5; ++i) {
        // The received atoms will be moved asynchronously
        auto recieved_left_atoms = comms.get(comm_type::LEFT, i - 1).then(hpx::launch::async, refit_to_box);
        auto recieved_right_atoms = comms.get(comm_type::RIGHT, i - 1).then(hpx::launch::async, refit_to_box);

        // Move our atoms
        my_box.move_atoms();

        // concatenate received atoms with our atoms
        left_buff = std::move(recieved_left_atoms.get()); // move_to_extend life to outer scope

        logger->info("Number of atoms before left insert {}", my_box.atoms.size());

        my_box.atoms.insert(my_box.atoms.end(), std::make_move_iterator(left_buff.begin()),
                            std::make_move_iterator(left_buff.end()));

        logger->info("Number of atoms after left insert {}", my_box.atoms.size());


        right_buff = std::move(recieved_right_atoms.get()); // move_to_extend life to outer scope
        logger->info("Number of atoms before right insert {}", my_box.atoms.size());


        my_box.atoms.insert(my_box.atoms.end(), std::make_move_iterator(right_buff.begin()),
                            std::make_move_iterator(right_buff.end()));
        logger->info("Number of atoms after after insert {}", my_box.atoms.size());


        auto inside_end = std::partition(my_box.atoms.begin(), my_box.atoms.end(), [&my_box](const Atom &atom) {
            return my_box.dimension.pointState(atom.position) == PointState::INSIDE;
        });
        auto left_end = std::partition(inside_end, my_box.atoms.end(), [&my_box](const Atom &atom) {
            return my_box.dimension.pointState(atom.position) == PointState::LEFT;
        });

        hpx::cout << "Finished step" << std::endl;


        left_buff.assign(inside_end, left_end);
        right_buff.assign(left_end, my_box.atoms.end());
        my_box.atoms.resize(inside_end - my_box.atoms.begin());

        left_send = comms.set(comm_type::LEFT, std::move(left_buff), i);
        right_send = comms.set(comm_type::RIGHT, std::move(right_buff), i);

        logger->info("After iteration {} {}", i, spdlog::fmt_lib::join(my_box.atoms, "\n"));

    }
    auto recieved_left_atoms = comms.get(comm_type::LEFT, 4).then(hpx::launch::async, refit_to_box);
    auto recieved_right_atoms = comms.get(comm_type::RIGHT, 4).then(hpx::launch::async, refit_to_box);
    left_buff = std::move(recieved_left_atoms.get()); // move_to_extend life to outer scope

    logger->info("Number of atoms before left insert {}", my_box.atoms.size());

    my_box.atoms.insert(my_box.atoms.end(), std::make_move_iterator(left_buff.begin()),
                        std::make_move_iterator(left_buff.end()));

    logger->info("Number of atoms after left insert {}", my_box.atoms.size());


    right_buff = std::move(recieved_right_atoms.get()); // move_to_extend life to outer scope
    my_box.atoms.insert(my_box.atoms.end(), std::make_move_iterator(right_buff.begin()),
                        std::make_move_iterator(right_buff.end()));
    logger->info("Number of atoms before right insert {}", my_box.atoms.size());
    logger->info("final number of my atoms {}", my_box.atoms.size());
    auto size_after_sim = hpx::collectives::all_reduce("number_of_atoms", my_box.atoms.size(),
                                                       [](auto left, auto right) {
                                                           return left + right;
                                                       }).get();

    logger->info("After simulation wer had {} atoms", size_after_sim);

    return hpx::finalize();
}

int main(int argc, char *argv[]) {

    using namespace hpx::program_options;



    // Initialize and run HPX, this example requires to run hpx_main on all
    // localities
    std::vector<std::string> const cfg = {
            "hpx.run_hpx_main!=1",
    };

    hpx::init_params init_args;
    init_args.cfg = cfg;


    return hpx::init(argc, argv, init_args);
}

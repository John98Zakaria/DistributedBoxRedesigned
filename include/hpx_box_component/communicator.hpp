//
// Created by jn98zk on 5/25/22.
//

#ifndef DISTRIBUTEDBOXREDESIGNED_COMMUNICATOR_HPP
#define DISTRIBUTEDBOXREDESIGNED_COMMUNICATOR_HPP

#include <hpx/channel.hpp>
#include <hpx/iostream.hpp>
#include <spdlog/fmt/fmt.h>

template<typename T>
struct communicator {
    enum neighbour {
        LEFT = 0,
        RIGHT = 1,
    };
    typedef hpx::distributed::channel<T> channel_type;
    std::array<channel_type, 2> recv;
    std::array<channel_type, 2> send;


    communicator(std::size_t my_rank, std::size_t num_ranks) {
        auto channel_left = "/box/left";
        auto channel_right = "/box/right";
        std::size_t right_neighbour_id = (my_rank + 1) % num_ranks;
        std::size_t left_neighbour_id = (((int) my_rank - 1) % (int) num_ranks + num_ranks) % num_ranks;

        send[RIGHT] = channel_type(hpx::find_here());
        send[LEFT] = channel_type(hpx::find_here());
        hpx::register_with_basename(channel_left, send[LEFT], my_rank);
        hpx::register_with_basename(channel_right, send[RIGHT], my_rank);
        recv[LEFT] = hpx::find_from_basename<channel_type>(channel_left, left_neighbour_id);
        recv[RIGHT] = hpx::find_from_basename<channel_type>(channel_right, right_neighbour_id);
        auto left_msg = fmt::format("{} has left neighbour {}\n", my_rank, left_neighbour_id);
        auto right_msg = fmt::format("{} has right neighbour {}\n", my_rank, right_neighbour_id);
        hpx::cout << left_msg << right_msg << std::flush;
    }

    auto set(neighbour direction, T &&data, std::size_t step) {
        return send[direction].set(hpx::launch::async, std::move(data), step);
    }

    auto get(neighbour direction, std::size_t step) {
        return recv[direction].get(hpx::launch::async, step);
    }


};

#endif //DISTRIBUTEDBOXREDESIGNED_COMMUNICATOR_HPP

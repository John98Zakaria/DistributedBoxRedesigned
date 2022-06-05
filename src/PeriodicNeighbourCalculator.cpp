//
// Created by jn98zk on 6/2/22.
//
#include "PeriodicNeighbourCalculator.hpp"

using namespace Geometry;

PeriodicNeighbourCalculator::PeriodicNeighbourCalculator(size_t myRank, const Coordinate3D<std::size_t> &nodeGridSize)
        : my_rank(myRank), node_grid_size(nodeGridSize), num_ranks(nodeGridSize.x * nodeGridSize.y * nodeGridSize.z) {
    my_position = calculate_grid_position(myRank, nodeGridSize);

}

PeriodicNeighbourCalculator::position_type PeriodicNeighbourCalculator::calculate_grid_position(const std::size_t rank,
                                                                                                const PeriodicNeighbourCalculator::position_type &nodeGridSize) noexcept {
    std::size_t x = rank % nodeGridSize.x;
    std::size_t y = (rank / nodeGridSize.x) % nodeGridSize.y;
    std::size_t z = ((rank / nodeGridSize.x) / nodeGridSize.y) % nodeGridSize.z;
    return {x, y, z};
}

std::size_t PeriodicNeighbourCalculator::flatten_coordinate(const PeriodicNeighbourCalculator::position_type &position,
                                                            const PeriodicNeighbourCalculator::position_type &nodeGridSize) noexcept {

    return position.z * (nodeGridSize.x * nodeGridSize.y) + position.x + position.y * nodeGridSize.x;
}

std::size_t PeriodicNeighbourCalculator::positive_mod_wrapp(long amount) const noexcept {
    return (((int) my_rank + amount) % (int) num_ranks + num_ranks) % num_ranks;
}

std::size_t PeriodicNeighbourCalculator::positive_mod_wrapp(std::size_t amount) const noexcept {
    return positive_mod_wrapp((long int) amount);
}

PeriodicNeighbourCalculator::position_type
PeriodicNeighbourCalculator::wrap_around_add(PeriodicNeighbourCalculator::position_type direction) const noexcept {
    position_type neighbour = my_position + direction;
    neighbour.x = (neighbour.x + node_grid_size.x) % node_grid_size.x;
    neighbour.y = (neighbour.y + node_grid_size.y) % node_grid_size.y;
    neighbour.z = (neighbour.z + node_grid_size.z) % node_grid_size.z;
    return neighbour;
}

std::size_t PeriodicNeighbourCalculator::get_neighbour_rank(NeighbourRelation relation) const noexcept {
    return flatten_coordinate(wrap_around_add(enum_to_direction(relation)), node_grid_size);
}

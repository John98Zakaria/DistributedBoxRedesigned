
#ifndef DISTRIBUTEDBOXREDESIGNED_CUBICNEIGHBOURCALCULATOR_HPP
#define DISTRIBUTEDBOXREDESIGNED_CUBICNEIGHBOURCALCULATOR_HPP

#include "Coordinate3D.hpp"

/**
 * Calculates all of the 27 neighbours that surround a node
 */
namespace Geometry {

    enum NeighbourRelation {
        PLANE_CENTER_LEFT,
        PLANE_CENTER_RIGHT,
        PLANE_CENTER_UP,
        PLANE_CENTER_DOWN,
        PLANE_CENTER_LEFT_UP,
        PLANE_CENTER_LEFT_DOWN,
        PLANE_CENTER_RIGHT_UP,
        PLANE_CENTER_RIGHT_DOWN,
        ABOVE_CENTER_LEFT,
        ABOVE_CENTER_RIGHT,
        ABOVE_CENTER_UP,
        ABOVE_CENTER,
        ABOVE_CENTER_DOWN,
        ABOVE_CENTER_LEFT_UP,
        ABOVE_CENTER_LEFT_DOWN,
        ABOVE_CENTER_RIGHT_UP,
        ABOVE_CENTER_RIGHT_DOWN,
        BELLOW_CENTER_LEFT,
        BELLOW_CENTER_RIGHT,
        BELLOW_CENTER_UP,
        BELLOW_CENTER,
        BELLOW_CENTER_DOWN,
        BELLOW_CENTER_LEFT_UP,
        BELLOW_CENTER_LEFT_DOWN,
        BELLOW_CENTER_RIGHT_UP,
        BELLOW_CENTER_RIGHT_DOWN,
    };

    constexpr std::array<NeighbourRelation, 26> NeighbourEnumIterable = {NeighbourRelation::PLANE_CENTER_LEFT,
                                                                         NeighbourRelation::PLANE_CENTER_RIGHT,
                                                                         NeighbourRelation::PLANE_CENTER_UP,
                                                                         NeighbourRelation::PLANE_CENTER_DOWN,
                                                                         NeighbourRelation::PLANE_CENTER_LEFT_UP,
                                                                         NeighbourRelation::PLANE_CENTER_LEFT_DOWN,
                                                                         NeighbourRelation::PLANE_CENTER_RIGHT_UP,
                                                                         NeighbourRelation::PLANE_CENTER_RIGHT_DOWN,
                                                                         NeighbourRelation::ABOVE_CENTER_LEFT,
                                                                         NeighbourRelation::ABOVE_CENTER_RIGHT,
                                                                         NeighbourRelation::ABOVE_CENTER_UP,
                                                                         NeighbourRelation::ABOVE_CENTER,
                                                                         NeighbourRelation::ABOVE_CENTER_DOWN,
                                                                         NeighbourRelation::ABOVE_CENTER_LEFT_UP,
                                                                         NeighbourRelation::ABOVE_CENTER_LEFT_DOWN,
                                                                         NeighbourRelation::ABOVE_CENTER_RIGHT_UP,
                                                                         NeighbourRelation::ABOVE_CENTER_RIGHT_DOWN,
                                                                         NeighbourRelation::BELLOW_CENTER_LEFT,
                                                                         NeighbourRelation::BELLOW_CENTER_RIGHT,
                                                                         NeighbourRelation::BELLOW_CENTER_UP,
                                                                         NeighbourRelation::BELLOW_CENTER,
                                                                         NeighbourRelation::BELLOW_CENTER_DOWN,
                                                                         NeighbourRelation::BELLOW_CENTER_LEFT_UP,
                                                                         NeighbourRelation::BELLOW_CENTER_LEFT_DOWN,
                                                                         NeighbourRelation::BELLOW_CENTER_RIGHT_UP,
                                                                         NeighbourRelation::BELLOW_CENTER_RIGHT_DOWN};

    class PeriodicNeighbourCalculator {
    public:
        using position_type = Coordinate3D<std::size_t>;

        PeriodicNeighbourCalculator(std::size_t myRank, const Coordinate3D<std::size_t> &nodeGridSize);


        static position_type
        calculate_grid_position(std::size_t rank, const position_type &nodeGridSize) noexcept;

        static std::size_t
        flatten_coordinate(const position_type &position, const position_type &nodeGridSize) noexcept;

        std::size_t positive_mod_wrapp(long int amount) const noexcept;

        std::size_t positive_mod_wrapp(std::size_t amount) const noexcept;

        static constexpr std::size_t positive_mod(long int number, long int amount, long int base) noexcept {
            return ((number + amount) % base + base) % base;
        }

        static constexpr position_type enum_to_direction(NeighbourRelation relation) {
            using dtype = std::size_t;
            switch (relation) {
                case PLANE_CENTER_LEFT:
                    return {(dtype) -1, 0, 0};
                case PLANE_CENTER_RIGHT:
                    return {1, 0, 0};;
                case PLANE_CENTER_UP:
                    return {0, (dtype) -1, 0};
                case PLANE_CENTER_DOWN:
                    return {0, 1, 0};
                case PLANE_CENTER_LEFT_UP:
                    return {(dtype) -1, (dtype) -1, 0};
                case PLANE_CENTER_LEFT_DOWN:
                    return {(dtype) -1, 1, 0};
                case PLANE_CENTER_RIGHT_UP:
                    return {(dtype) 1, (dtype) -1, 0};
                case PLANE_CENTER_RIGHT_DOWN:
                    return {(dtype) 1, (dtype) 1, 0};
                case ABOVE_CENTER_LEFT:
                    return {(dtype) -1, 0, (dtype) -1};
                case ABOVE_CENTER_RIGHT:
                    return {1, 0, (dtype) -1};
                case ABOVE_CENTER_UP:
                    return {0, (dtype) -1, (dtype) -1};
                case ABOVE_CENTER:
                    return {0, 0, (dtype) -1};
                case ABOVE_CENTER_DOWN:
                    return {0, 1, (dtype) -1};
                case ABOVE_CENTER_LEFT_UP:
                    return {(dtype) -1, (dtype) -1, (dtype) -1};
                case ABOVE_CENTER_LEFT_DOWN:
                    return {(dtype) -1, (dtype) 1, (dtype) -1};
                case ABOVE_CENTER_RIGHT_UP:
                    return {(dtype) 1, (dtype) -1, (dtype) -1};
                case ABOVE_CENTER_RIGHT_DOWN:
                    return {(dtype) 1, (dtype) 1, (dtype) -1};
                case BELLOW_CENTER_LEFT:
                    return {(dtype) -1, 0, (dtype) 1};
                case BELLOW_CENTER_RIGHT:
                    return {1, 0, (dtype) 1};
                case BELLOW_CENTER_UP:
                    return {0, (dtype) -1, (dtype) 1};
                case BELLOW_CENTER:
                    return {0, 0, (dtype) 1};
                case BELLOW_CENTER_DOWN:
                    return {0, 1, (dtype) 1};
                case BELLOW_CENTER_LEFT_UP:
                    return {(dtype) -1, (dtype) -1, (dtype) 1};
                case BELLOW_CENTER_LEFT_DOWN:
                    return {(dtype) -1, (dtype) 1, (dtype) 1};
                case BELLOW_CENTER_RIGHT_UP:
                    return {(dtype) 1, (dtype) -1, (dtype) 1};
                case BELLOW_CENTER_RIGHT_DOWN:
                    return {(dtype) 1, (dtype) 1, (dtype) 1};
            }
            return {0, 0, 0};
        }

        static constexpr std::size_t positive_mod(std::size_t number, std::size_t amount, std::size_t base) noexcept {
            return positive_mod((long int) number, (long int) amount, (long int) base);
        }

        position_type wrap_around_add(position_type direction) const noexcept;

        std::size_t get_neighbour_rank(NeighbourRelation relation) const noexcept;


    private:
        std::size_t my_rank;
        std::size_t num_ranks;
        position_type node_grid_size{};
        position_type my_position{};
        std::array<std::size_t, 26> neighbour_index{};


    };
}

#endif //DISTRIBUTEDBOXREDESIGNED_CUBICNEIGHBOURCALCULATOR_HPP

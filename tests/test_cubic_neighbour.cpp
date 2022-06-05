//
// Created by jn98zk on 6/2/22.
//
#include "PeriodicNeighbourCalculator.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <spdlog/fmt/fmt.h>

using Geometry::PeriodicNeighbourCalculator;

template<typename T, typename U>
struct FlatHelper {
    T input;
    U expected;
};

TEST_CASE("Calculates the flatted index correctly", "[CubicNeighbourCalc]") {
    using coord = PeriodicNeighbourCalculator::position_type;
    using fixure = FlatHelper<coord, std::size_t>;
    constexpr coord gridSize{3, 3, 3};
    auto [input, expected] = GENERATE(fixure{{0, 0, 0}, 0}, fixure{{1, 0, 0}, 1}, fixure{{0, 1, 0}, 3},
                                      fixure{{0, 0, 1}, 9}, fixure{{1, 0, 1}, 10}, fixure{{1, 1, 1}, 13});
    DYNAMIC_SECTION("Input: " << input << " expected " << expected) {
        CHECK(PeriodicNeighbourCalculator::flatten_coordinate(input, gridSize) == expected);

    }
}

TEST_CASE("Calculates the neighbour index correctly for one rank", "[CubicNeighbourCalc]") {
    using coord = PeriodicNeighbourCalculator::position_type;
    using fixure = FlatHelper<coord, std::size_t>;
    using neigbour = Geometry::NeighbourRelation;
    constexpr coord gridSize{1, 1, 1};

    PeriodicNeighbourCalculator calculator(0, gridSize);
    auto input = GENERATE(from_range(Geometry::NeighbourEnumIterable.begin(), Geometry::NeighbourEnumIterable.end()));
    DYNAMIC_SECTION("Input: " << input) {
        CHECK(calculator.get_neighbour_rank(input) == 0);
    }
}

TEST_CASE("Calculates the neighbour index correctly for two ranks", "[CubicNeighbourCalc]") {
    using coord = PeriodicNeighbourCalculator::position_type;
    using fixure = FlatHelper<coord, std::size_t>;
    using neigbour = Geometry::NeighbourRelation;
    constexpr coord gridSize{2, 1, 1};

    PeriodicNeighbourCalculator calculator0(0, gridSize);
    auto input = GENERATE(from_range(Geometry::NeighbourEnumIterable.begin(), Geometry::NeighbourEnumIterable.end()));
    CHECK(calculator0.get_neighbour_rank(neigbour::PLANE_CENTER_LEFT) == 1);
    CHECK(calculator0.get_neighbour_rank(neigbour::PLANE_CENTER_RIGHT) == 1);
    CHECK(calculator0.get_neighbour_rank(neigbour::PLANE_CENTER_UP) == 0);
    CHECK(calculator0.get_neighbour_rank(neigbour::PLANE_CENTER_DOWN) == 0);
    CHECK(calculator0.get_neighbour_rank(neigbour::PLANE_CENTER_LEFT_UP) == 1);
    CHECK(calculator0.get_neighbour_rank(neigbour::PLANE_CENTER_LEFT_DOWN) == 1);
    CHECK(calculator0.get_neighbour_rank(neigbour::PLANE_CENTER_RIGHT_UP) == 1);
    CHECK(calculator0.get_neighbour_rank(neigbour::PLANE_CENTER_RIGHT_DOWN) == 1);
    CHECK(calculator0.get_neighbour_rank(neigbour::ABOVE_CENTER_LEFT) == 1);
    CHECK(calculator0.get_neighbour_rank(neigbour::ABOVE_CENTER_RIGHT) == 1);
    CHECK(calculator0.get_neighbour_rank(neigbour::ABOVE_CENTER_UP) == 0);
    CHECK(calculator0.get_neighbour_rank(neigbour::ABOVE_CENTER) == 0);
    CHECK(calculator0.get_neighbour_rank(neigbour::ABOVE_CENTER_DOWN) == 0);
    CHECK(calculator0.get_neighbour_rank(neigbour::ABOVE_CENTER_LEFT_UP) == 1);
    CHECK(calculator0.get_neighbour_rank(neigbour::ABOVE_CENTER_LEFT_DOWN) == 1);
    CHECK(calculator0.get_neighbour_rank(neigbour::ABOVE_CENTER_RIGHT_UP) == 1);
    CHECK(calculator0.get_neighbour_rank(neigbour::ABOVE_CENTER_RIGHT_DOWN) == 1);
    CHECK(calculator0.get_neighbour_rank(neigbour::BELLOW_CENTER_LEFT) == 1);
    CHECK(calculator0.get_neighbour_rank(neigbour::BELLOW_CENTER_RIGHT) == 1);
    CHECK(calculator0.get_neighbour_rank(neigbour::BELLOW_CENTER_UP) == 0);
    CHECK(calculator0.get_neighbour_rank(neigbour::BELLOW_CENTER) == 0);
    CHECK(calculator0.get_neighbour_rank(neigbour::BELLOW_CENTER_DOWN) == 0);
    CHECK(calculator0.get_neighbour_rank(neigbour::BELLOW_CENTER_LEFT_UP) == 1);
    CHECK(calculator0.get_neighbour_rank(neigbour::BELLOW_CENTER_LEFT_DOWN) == 1);
    CHECK(calculator0.get_neighbour_rank(neigbour::BELLOW_CENTER_RIGHT_UP) == 1);
    CHECK(calculator0.get_neighbour_rank(neigbour::BELLOW_CENTER_RIGHT_DOWN) == 1);
}

constexpr auto enum_to_string(Geometry::NeighbourRelation relation) {
    switch (relation) {
        case Geometry::PLANE_CENTER_LEFT:
            return "Geometry::PLANE_CENTER_LEFT:";
        case Geometry::PLANE_CENTER_RIGHT:
            return "Geometry::PLANE_CENTER_RIGHT:";
        case Geometry::PLANE_CENTER_UP:
            return "Geometry::PLANE_CENTER_UP:";
        case Geometry::PLANE_CENTER_DOWN:
            return "Geometry::PLANE_CENTER_DOWN:";
        case Geometry::PLANE_CENTER_LEFT_UP:
            return "Geometry::PLANE_CENTER_LEFT_UP:";
        case Geometry::PLANE_CENTER_LEFT_DOWN:
            return "Geometry::PLANE_CENTER_LEFT_DOWN:";
        case Geometry::PLANE_CENTER_RIGHT_UP:
            return "Geometry::PLANE_CENTER_RIGHT_UP:";
        case Geometry::PLANE_CENTER_RIGHT_DOWN:
            return "Geometry::PLANE_CENTER_RIGHT_DOWN:";
        case Geometry::ABOVE_CENTER_LEFT:
            return "Geometry::ABOVE_CENTER_LEFT:";
        case Geometry::ABOVE_CENTER_RIGHT:
            return "Geometry::ABOVE_CENTER_RIGHT:";
        case Geometry::ABOVE_CENTER_UP:
            return "Geometry::ABOVE_CENTER_UP:";
        case Geometry::ABOVE_CENTER:
            return "Geometry::ABOVE_CENTER:";
        case Geometry::ABOVE_CENTER_DOWN:
            return "Geometry::ABOVE_CENTER_DOWN:";
        case Geometry::ABOVE_CENTER_LEFT_UP:
            return "Geometry::ABOVE_CENTER_LEFT_UP:";
        case Geometry::ABOVE_CENTER_LEFT_DOWN:
            return "Geometry::ABOVE_CENTER_LEFT_DOWN:";
        case Geometry::ABOVE_CENTER_RIGHT_UP:
            return "Geometry::ABOVE_CENTER_RIGHT_UP:";
        case Geometry::ABOVE_CENTER_RIGHT_DOWN:
            return "Geometry::ABOVE_CENTER_RIGHT_DOWN:";
        case Geometry::BELLOW_CENTER_LEFT:
            return "Geometry::BELLOW_CENTER_LEFT:";
        case Geometry::BELLOW_CENTER_RIGHT:
            return "Geometry::BELLOW_CENTER_RIGHT:";
        case Geometry::BELLOW_CENTER_UP:
            return "Geometry::BELLOW_CENTER_UP:";
        case Geometry::BELLOW_CENTER:
            return "Geometry::BELLOW_CENTER:";
        case Geometry::BELLOW_CENTER_DOWN:
            return "Geometry::BELLOW_CENTER_DOWN:";
        case Geometry::BELLOW_CENTER_LEFT_UP:
            return "Geometry::BELLOW_CENTER_LEFT_UP:";
        case Geometry::BELLOW_CENTER_LEFT_DOWN:
            return "Geometry::BELLOW_CENTER_LEFT_DOWN:";
        case Geometry::BELLOW_CENTER_RIGHT_UP:
            return "Geometry::BELLOW_CENTER_RIGHT_UP:";
        case Geometry::BELLOW_CENTER_RIGHT_DOWN:
            return "Geometry::BELLOW_CENTER_RIGHT_DOWN:";
        default:
            return "Unknown";
    }
}


TEST_CASE("Calculates the neighbour index correctly rank 13 3x3x3", "[CubicNeighbourCalc]") {
    using coord = PeriodicNeighbourCalculator::position_type;
    constexpr coord gridSize{3, 3, 3};
    constexpr auto expected_neigbours = std::array<std::size_t, 26>{12, 14, 10, 16, 9, 15, 11, 17, 3, 5, 1, 4, 7, 0, 6,
                                                                    2, 8, 21, 23, 19, 22, 25, 18, 24, 20, 26};
    PeriodicNeighbourCalculator calculator13(13, gridSize);
    auto id = GENERATE(range(0, 26));
    auto expected = expected_neigbours[id];
    auto input = Geometry::NeighbourEnumIterable[id];
    DYNAMIC_SECTION("For Rank 13 Input: " << enum_to_string(input) << " expected " << expected) {
        CHECK(calculator13.get_neighbour_rank(input) == expected);

    }

}

TEST_CASE("Calculates the neighbour index correctly rank 12 3x3x3", "[CubicNeighbourCalc]") {
    using coord = PeriodicNeighbourCalculator::position_type;
    constexpr coord gridSize{3, 3, 3};
    constexpr auto expected_neigbours = std::array<std::size_t, 26>{14, 13, 9, 15, 11, 17, 10, 16, 5, 4, 0, 3, 6, 2, 8,
                                                                    1, 7, 23, 22, 18, 21, 24, 20, 26, 19, 25};


    PeriodicNeighbourCalculator calculator13(12, gridSize);
    auto id = GENERATE(range(0, 26));
    auto expected = expected_neigbours[id];
    auto input = Geometry::NeighbourEnumIterable[id];
    DYNAMIC_SECTION("For Rank 12 Input: " << enum_to_string(input) << " expected " << expected) {
        CHECK(calculator13.get_neighbour_rank(input) == expected);

    }
}

TEST_CASE("Calculates the neighbour index correctly rank 20 6x4x2", "[CubicNeighbourCalc]") {
    using coord = PeriodicNeighbourCalculator::position_type;
    constexpr coord gridSize{6, 4, 2};


    PeriodicNeighbourCalculator calculator13(20, gridSize);
    auto id = GENERATE(range(0, 26));
    constexpr auto expected_neigbours = std::array<std::size_t, 26>{19, 21, 14, 2, 13, 1, 15, 3, 43, 45, 38, 44, 26, 37,
                                                                    25, 39, 27, 43, 45, 38, 44, 26, 37, 25, 39, 27};
    auto expected = expected_neigbours[id];
    auto input = Geometry::NeighbourEnumIterable[id];
    DYNAMIC_SECTION("For Rank 20 Input: " << enum_to_string(input) << " expected " << expected) {
        CHECK(calculator13.get_neighbour_rank(input) == expected);

    }
}

TEST_CASE("3D to 1D to 3D coordinates", "[CubicNeighbourCalc]") {
    using coord = PeriodicNeighbourCalculator::position_type;
    coord gridSize{4, 4, 4};
    auto rank = GENERATE(range(0, 64));
    auto pos = PeriodicNeighbourCalculator::calculate_grid_position(rank, gridSize);
    auto flattened = PeriodicNeighbourCalculator::flatten_coordinate(pos, gridSize);

    DYNAMIC_SECTION(fmt::format("Started with rank {}, 3D Rank to {},{},{}, flattened to {}", rank, pos.y, pos.x, pos.z,
                                flattened)) {
        CHECK(rank == flattened);
    }

}

//TEST_CASE("Calculates the neighbour index correctly rank 12 3x3x3", "[CubicNeighbourCalc]") {
//    using coord = CubicNeighbourCalculator::position_type;
//    constexpr coord gridSize{3, 3, 3};
//    constexpr auto expected_neigbours = std::array<std::size_t, 26>{14,;
//    CubicNeighbourCalculator calculator13(13, gridSize);
//    auto id = GENERATE(range(0, 26));
//    auto expected = expected_neigbours[id];
//    auto input = Geometry::NeighbourEnumIterable[id];
//    DYNAMIC_SECTION("For Rank 12 Input: " << enum_to_string(input) << " expected " << expected) {
//        CHECK(calculator13.get_neighbour_rank(input) == expected);
//
//    }
//    CubicNeighbourCalculator calculator12(12, gridSize);
//
//
//}
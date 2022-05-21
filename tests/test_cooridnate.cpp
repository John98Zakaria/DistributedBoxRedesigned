//
// Created by jn98zk on 5/19/22.
//
#include <catch2/catch_test_macros.hpp>

#include "Coordinate2D.hpp"

TEST_CASE("Empty initialization is zero", "[Coordinate2D]") {
    Coordinate2D coord;
    REQUIRE(coord.x == 0);
    REQUIRE(coord.y == 0);
}

TEST_CASE("Addition Works", "[Coordinate2D]") {
    Coordinate2D coord;
    Coordinate2D cord2{1, 2};
    auto res = coord + cord2;
    REQUIRE(coord.x == 0);
    REQUIRE(coord.y == 0);
    REQUIRE(cord2.x == 1);
    REQUIRE(cord2.y == 2);
    REQUIRE(cord2 == res);
    REQUIRE(cord2 != coord);
}

TEST_CASE("Random random_coord Works", "[Coordinate2D]") {
    auto coord = Coordinate2D::random_coord(Coordinate2D{0, 1}, Coordinate2D{0, 1});
    auto coord1 = Coordinate2D::random_coord(Coordinate2D{0, 1}, Coordinate2D{0, 1});
    REQUIRE(coord != coord1);
}

TEST_CASE("Copy Assignment Constructor works", "[Coordinate2D]") {
    auto coord = Coordinate2D::random_coord(Coordinate2D{0, 1}, Coordinate2D{0, 1});
    auto coord_Copy = coord;
    REQUIRE(coord == coord_Copy);
    coord.y = 5;
    REQUIRE(coord != coord_Copy);

}

TEST_CASE("Copy Constructor works", "[Coordinate2D]") {
    auto coord = Coordinate2D::random_coord(Coordinate2D{0, 1}, Coordinate2D{0, 1});
    Coordinate2D coord_copy(coord);
    REQUIRE(coord == coord_copy);
    coord.y = 5;
    REQUIRE(coord != coord_copy);

}
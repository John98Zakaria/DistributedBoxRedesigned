//
// Created by jn98zk on 5/19/22.
//
#include <catch2/catch_test_macros.hpp>

#include "Coordinate2D.hpp"

TEST_CASE("Empty initialization is zero", "[Coordinate2D]") {
    Coordinate2D GEOMETRY;
    REQUIRE(GEOMETRY.x == 0);
    REQUIRE(GEOMETRY.y == 0);
}

TEST_CASE("Addition Works", "[Coordinate2D]") {
    Coordinate2D GEOMETRY;
    Coordinate2D cord2{1, 2};
    auto res = GEOMETRY + cord2;
    REQUIRE(GEOMETRY.x == 0);
    REQUIRE(GEOMETRY.y == 0);
    REQUIRE(cord2.x == 1);
    REQUIRE(cord2.y == 2);
    REQUIRE(cord2 == res);
    REQUIRE(cord2 != GEOMETRY);
}

TEST_CASE("Random random_coord Works", "[Coordinate2D]") {
    auto GEOMETRY = Coordinate2D::random_coord(Coordinate2D{0, 1}, Coordinate2D{0, 1});
    auto GEOMETRY1 = Coordinate2D::random_coord(Coordinate2D{0, 1}, Coordinate2D{0, 1});
    REQUIRE(GEOMETRY!=GEOMETRY1);
}
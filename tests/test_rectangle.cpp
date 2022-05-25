//
// Created by jn98zk on 5/19/22.
//
#include <catch2/catch_test_macros.hpp>
#include "Rectangle.hpp"

using namespace Geometry;

TEST_CASE("Can Detect PointState", "[Rectangle]") {
    Rectangle rectangle({0, 0}, {5, 5});
    Coordinate2D inside{2.5, 2.5};
    Coordinate2D left{-1, 0};
    Coordinate2D above{0, -1};
    Coordinate2D below{0, 6};
    Coordinate2D right{6, 0};

    CHECK(rectangle.pointState(inside) == PointState::INSIDE);
    CHECK(rectangle.pointState(left) == PointState::LEFT);
    CHECK(rectangle.pointState(right) == PointState::RIGHT);
    CHECK(rectangle.pointState(above) == PointState::Above);
    CHECK(rectangle.pointState(below) == PointState::Bellow);

}



TEST_CASE("Combining Point-states", "[Rectangle]") {
    auto state = PointState::LEFT | PointState::Above;

    CHECK(PointState::LEFT_ABOVE == state);
    auto state2 = PointState::LEFT | PointState::Bellow;
    CHECK(PointState::LEFT_BELLOW == state2);

    auto state3 = PointState::RIGHT | PointState::Above;
    CHECK(PointState::RIGHT_ABOVE == state3);

    auto state4 = PointState::RIGHT | PointState::Bellow;
    CHECK(PointState::RIGHT_BELLOW == state4);

}


TEST_CASE("Can calculate dimensions", "[Rectangle]") {
    Rectangle rectangle({1, 1}, {5, 6});
    CHECK(rectangle.width() == 4);
    CHECK(rectangle.height() == 5);
    CHECK(rectangle.area() == 20);

}

TEST_CASE("Can get_copied", "[Rectangle]") {
    Rectangle rectangle({1, 1}, {5, 6});
    Rectangle rectangle_copy(rectangle);
    CHECK(rectangle == rectangle_copy);
    auto rectangle_copy2 = rectangle;

    rectangle_copy.bottom_right.x = 6;
    CHECK(rectangle_copy != rectangle);
    CHECK(rectangle_copy != rectangle_copy2);

}
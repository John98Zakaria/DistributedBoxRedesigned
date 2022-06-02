//
// Created by jn98zk on 5/19/22.
//
// This is a personal academic project. Dear PVS-Studio, please check it.

#include "Rectangle.hpp"

using namespace Geometry;

Rectangle::Rectangle(const Coordinate2D &topLeft, const Coordinate2D &bottomRight) : top_left(topLeft),
                                                                                     bottom_right(bottomRight) {
    if (topLeft.x > bottomRight.x || topLeft.y > bottomRight.y) {
        throw std::runtime_error("Invalid Rectangle");
    }
}

double Rectangle::width() const noexcept {
    return bottom_right.x - top_left.x;

}

double Rectangle::height() const noexcept {
    return bottom_right.y - top_left.y;
}

double Rectangle::area() const noexcept {
    return width() * height();
}

PointState Rectangle::pointState(const Coordinate2D &cord) const noexcept {
    auto state = PointState::NONE;
    if (cord.x > bottom_right.x) {
        state = state | PointState::RIGHT;
    } else if (cord.x < top_left.x) {
        state = state | PointState::LEFT;
    }
    if (cord.y > bottom_right.y) {
        state = state | PointState::Bellow;
    } else if (cord.y < top_left.y) {
        state = state | PointState::Above;
    }
    if (state == PointState::NONE) {
        return PointState::INSIDE;
    }
    return state;
}

void Rectangle::refit_into_container(Coordinate2D &coordinate) const noexcept {
    switch (pointState(coordinate)) {
        case PointState::INSIDE:
            break;
        case PointState::LEFT:
            coordinate.x += width();
            break;
        case PointState::RIGHT:
            coordinate.x -= width();
            break;
        case PointState::Bellow:
            coordinate.y -= height();
            break;
        case PointState::Above:
            coordinate.y += width();
            break;
        case PointState::LEFT_ABOVE:
            coordinate.x += width();
            coordinate.y += width();
            break;
        case PointState::LEFT_BELLOW:
            coordinate.x += width();
            coordinate.y -= height();

            break;
        case PointState::RIGHT_ABOVE:
            coordinate.x -= width();
            coordinate.y += width();
            break;
        case PointState::RIGHT_BELLOW:
            coordinate.x -= width();
            coordinate.y -= height();
            break;
        case PointState::NONE:
            break;
    }
}


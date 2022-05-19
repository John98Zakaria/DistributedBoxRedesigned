//
// Created by jn98zk on 5/19/22.
//
#include "../include/Rectangle.hpp"

Rectangle::Rectangle(const Coordinate2D &topLeft, const Coordinate2D &bottomRight) : top_left(topLeft),
                                                                                     bottom_right(bottomRight) {
    if (topLeft.x > bottomRight.y || topLeft.y > bottomRight.y) {
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
    if (cord.x > bottom_right.x) {
        return PointState::RIGHT;
    } else if (cord.x < top_left.x) {
        return PointState::LEFT;
    } else if (cord.y > bottom_right.y) {
        return PointState::Bellow;
    } else if (cord.y < top_left.y) {
        return PointState::Above;
    }
    return PointState::INSIDE;
}


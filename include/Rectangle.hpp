//
// Created by jn98zk on 5/19/22.
//

#ifndef DISTRIBUTEDBOXREDESIGNED_RECTANGLE_HPP
#define DISTRIBUTEDBOXREDESIGNED_RECTANGLE_HPP

enum struct PointState {
    INSIDE = 0,
    LEFT = 1,
    RIGHT = 2,
    Bellow = 3,
    Above = 4
};


#include "Coordinate2D.hpp"
#include "spdlog/fmt/ostr.h" // must be included

struct Rectangle {
    Coordinate2D top_left;
    Coordinate2D bottom_right;

    Rectangle(const Coordinate2D &topLeft, const Coordinate2D &bottomRight);

    double width() const noexcept;

    [[nodiscard]]  double height() const noexcept;

    [[nodiscard]]  double area() const noexcept;

    [[nodiscard]]  PointState pointState(const Coordinate2D &cord) const noexcept;

    bool operator==(const Rectangle &other) const noexcept {
        return top_left == other.top_left && bottom_right == other.bottom_right;
    }

    bool operator!=(const Rectangle &other) const noexcept {
        return !((*this) == other);
    }

    template<typename OStream>
    friend OStream &operator<<(OStream &os, const Rectangle &c) {
        return os << spdlog::fmt_lib::format("Rectangle(top_left={},bottom_right={})", c.top_left, c.bottom_right);

    }
};


#endif //DISTRIBUTEDBOXREDESIGNED_RECTANGLE_HPP

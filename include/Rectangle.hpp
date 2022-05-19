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

struct Rectangle {
    Coordinate2D top_left;
    Coordinate2D bottom_right;

    Rectangle(const Coordinate2D &topLeft, const Coordinate2D &bottomRight);

    double width() const noexcept;

    [[nodiscard]]  double height() const noexcept;

    [[nodiscard]]  double area() const noexcept;

    [[nodiscard]]  PointState pointState(const Coordinate2D &cord) const noexcept;
};


#endif //DISTRIBUTEDBOXREDESIGNED_RECTANGLE_HPP

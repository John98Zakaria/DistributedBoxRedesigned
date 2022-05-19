//
// Created by jn98zk on 5/19/22.
//

#ifndef DISTRIBUTEDBOXREDESIGNED_RECTANGLE_HPP
#define DISTRIBUTEDBOXREDESIGNED_RECTANGLE_HPP

#include "Coordinate2D.hpp"
enum struct PointState {
    INSIDE = 0,
    LEFT = 1,
    RIGHT = 2,
    Bellow = 3,
    Above = 4
};



struct Rectangle {
    Coordinate2D top_left;
    Coordinate2D bottom_right;

    Rectangle(const Coordinate2D &topLeft, const Coordinate2D &bottomRight);

    [[nodiscard]] constexpr double width() const noexcept;

    [[nodiscard]] constexpr double height() const noexcept;

    [[nodiscard]] constexpr double area() const noexcept;

    [[nodiscard]] constexpr PointState pointState(const Coordinate2D &cord) const noexcept;
};


#endif //DISTRIBUTEDBOXREDESIGNED_RECTANGLE_HPP

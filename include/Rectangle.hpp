//
// Created by jn98zk on 5/19/22.
//

#ifndef DISTRIBUTEDBOXREDESIGNED_RECTANGLE_HPP
#define DISTRIBUTEDBOXREDESIGNED_RECTANGLE_HPP

#include "Coordinate2D.hpp"
#include "spdlog/fmt/ostr.h" // must be included


namespace Geometry {
    enum class PointState : std::uint8_t {
        NONE = 0,
        INSIDE = 1,
        LEFT = 2,
        RIGHT = 4,
        Bellow = 8,
        Above = 16,

        LEFT_ABOVE = LEFT | Above,
        LEFT_BELLOW = LEFT | Bellow,
        RIGHT_ABOVE = RIGHT | Above,
        RIGHT_BELLOW = RIGHT | Bellow,

    };

    inline PointState operator|(PointState lhs, PointState rhs) {
        return static_cast<PointState>(
                static_cast<std::underlying_type_t<PointState>>(lhs) |
                static_cast<std::underlying_type_t<PointState>>(rhs)
        );
    }

    inline PointState operator&(const PointState lhs, const PointState rhs) {
        return static_cast<PointState>(
                static_cast<std::underlying_type_t<PointState>>(lhs) &
                static_cast<std::underlying_type_t<PointState>>(rhs)
        );
    }

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

}


#endif //DISTRIBUTEDBOXREDESIGNED_RECTANGLE_HPP

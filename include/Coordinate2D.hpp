//
// Created by jn98zk on 5/11/22.
//


#ifndef DISTIBUTEDBOX_Coordinate2D_HPP
#define DISTIBUTEDBOX_Coordinate2D_HPP


#include <cstdio>
#include <complex>
#include <random>
#include <spdlog/spdlog.h>
namespace Geometry {
    struct Coordinate2D {
        double x{};
        double y{};

        Coordinate2D operator-(const Coordinate2D &cord) const noexcept;

        Coordinate2D operator+(const Coordinate2D &cord) const noexcept;

        Coordinate2D &operator+=(const Coordinate2D &cord) noexcept;

        Coordinate2D &operator-=(const Coordinate2D &cord) noexcept;

        bool operator==(const Coordinate2D &cord) const noexcept;

        bool operator!=(const Coordinate2D &cord) const noexcept;

        [[nodiscard]] double norm() const noexcept;


        static Coordinate2D random_coord(const Coordinate2D &topleft, const Coordinate2D &bottomright) noexcept;


        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & x & y;
        }

        template<typename OStream>
        friend OStream &operator<<(OStream &os, const Coordinate2D &c) {
            return os << spdlog::fmt_lib::format("({:.3f},{:.3f})", c.x, c.y);

        }


    };

}


#endif //DISTIBUTEDBOX_Coordinate2D_HPP

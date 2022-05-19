//
// Created by jn98zk on 5/11/22.
//


#ifndef DISTIBUTEDBOX_Coordinate2D_HPP
#define DISTIBUTEDBOX_Coordinate2D_HPP


#include <cstdio>
#include <complex>
#include <random>

struct Coordinate2D {
    double x{};
    double y{};

    constexpr Coordinate2D operator-(const Coordinate2D &cord) const noexcept;

    constexpr Coordinate2D operator+(const Coordinate2D &cord) const noexcept;

    constexpr Coordinate2D &operator+=(const Coordinate2D &cord) noexcept;

    constexpr Coordinate2D &operator-=(const Coordinate2D &cord) noexcept;

    constexpr bool operator==(const Coordinate2D &cord) const noexcept;
    constexpr bool operator!=(const Coordinate2D &cord) const noexcept;

    [[nodiscard]] double norm() const noexcept;


    static Coordinate2D random_coord(const Coordinate2D &topleft, const Coordinate2D &bottomright) noexcept;


    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & x & y;
    }


};


#endif //DISTIBUTEDBOX_Coordinate2D_HPP

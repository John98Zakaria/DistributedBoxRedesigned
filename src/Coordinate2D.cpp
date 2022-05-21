//
// Created by jn98zk on 5/19/22.
//
// This is a personal academic project. Dear PVS-Studio, please check it.


#include "Coordinate2D.hpp"

using namespace Geometry;

Coordinate2D Coordinate2D::operator-(const Coordinate2D &cord) const noexcept {
    return {cord.x - x, cord.y - y};
}

Coordinate2D Coordinate2D::operator+(const Coordinate2D &cord) const noexcept {
    return {cord.x + x, cord.y + y};
}

Coordinate2D &Coordinate2D::operator+=(const Coordinate2D &cord) noexcept {
    x += cord.x;
    y += cord.y;
    return *this;
}

Coordinate2D &Coordinate2D::operator-=(const Coordinate2D &cord) noexcept {
    x -= cord.x;
    y -= cord.y;
    return *this;
}

bool Coordinate2D::operator==(const Coordinate2D &cord) const noexcept {
    return x == cord.x && y == cord.y;
}

bool Coordinate2D::operator!=(const Coordinate2D &cord) const noexcept {
    return !(*this == cord);
}

double Coordinate2D::norm() const noexcept {
    return std::sqrt(x * x + y * y);
}

Coordinate2D Coordinate2D::random_coord(const Coordinate2D &topleft, const Coordinate2D &bottomright) noexcept {
    std::random_device dev;
    std::uniform_real_distribution<double> x_rand(topleft.x, bottomright.x);
    std::uniform_real_distribution<double> y_rand(topleft.x, bottomright.y);

    return {x_rand(dev), y_rand(dev)};
}

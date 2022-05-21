//
// Created by jn98zk on 5/11/22.
//

#ifndef DISTIBUTEDBOX_ATOM_HPP
#define DISTIBUTEDBOX_ATOM_HPP

#include "Coordinate2D.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

struct Atom {
    Coordinate2D position;
    std::size_t id{};
    Coordinate2D direction;

    void move() {
        position += direction;
    }

    bool operator==(const Atom &rhs) const noexcept {
        return position == rhs.position &&
               id == rhs.id &&
               direction == rhs.direction;
    }

    bool operator!=(const Atom &rhs) const noexcept {
        return !(rhs == *this);
    }

    template<typename OStream>
    friend OStream &operator<<(OStream &os, const Atom &c) {
        return os << spdlog::fmt_lib::format("Atom(id={} ,direction={} ,position={})", c.id, c.direction, c.position);

    }
};


#endif //DISTIBUTEDBOX_ATOM_HPP

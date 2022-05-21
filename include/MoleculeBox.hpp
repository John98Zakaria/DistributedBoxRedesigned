//
// Created by jn98zk on 5/20/22.
//

#ifndef DISTRIBUTEDBOXREDESIGNED_MOLECULEBOX_HPP
#define DISTRIBUTEDBOXREDESIGNED_MOLECULEBOX_HPP

#include "Rectangle.hpp"
#include "Atom.hpp"
#include <utility>
#include <vector>
#include <algorithm>
#include <execution>

class MoleculeBox {
    Rectangle dimension;
    std::vector<Atom> atoms;
public:
    MoleculeBox(const Rectangle &dimension, const std::vector<Atom> &atoms) : dimension(dimension), atoms(atoms) {}

    void step() noexcept;

    void reposition_atoms() noexcept;

    void reposition_atom(Atom &atom) noexcept;

    const Rectangle &getDimension() const;

    const std::vector<Atom> &getAtoms() const;

    void move_atoms() noexcept;

    template<typename OStream>
    friend OStream &operator<<(OStream &os, const MoleculeBox &c) {
        return os << spdlog::fmt_lib::format("MoleculeBox(dimensions={},size={})", c.dimension, c.atoms.size());

    }
};


#endif //DISTRIBUTEDBOXREDESIGNED_MOLECULEBOX_HPP

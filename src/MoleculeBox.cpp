#include "MoleculeBox.hpp"
// This is a personal academic project. Dear PVS-Studio, please check it.

//
// Created by jn98zk on 5/20/22.
//

using namespace Domain;

void MoleculeBox::reposition_atoms() noexcept {
    std::for_each(atoms.begin(), atoms.end(), [this](Atom &atom) { reposition_atom(atom); });
}

void MoleculeBox::reposition_atom(Atom &atom) noexcept {
    dimension.refit_into_container(atom.position);
}

void MoleculeBox::move_atoms() noexcept {
    std::for_each(atoms.begin(), atoms.end(), [](Atom &atom) {
        atom.move();
    });
}

void MoleculeBox::step() noexcept {
    move_atoms();
    reposition_atoms();
}

const Rectangle &MoleculeBox::getDimension() const {
    return dimension;
}

const std::vector<Atom> &MoleculeBox::getAtoms() const {
    return atoms;
}

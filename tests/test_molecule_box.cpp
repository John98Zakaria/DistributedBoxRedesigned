#include "MoleculeBox.hpp"
#include <catch2/catch_test_macros.hpp>


TEST_CASE("Reposition Atom", "[MoleculeBox]") {
    std::vector<Atom> atoms{{{0, 0}, 1, {0, 1}}};
    MoleculeBox moleculeBox({{0, 0},
                             {5, 5}}, atoms);
    SECTION("Right Atom is repositioned correctly") {
        atoms[0].position = {6, 0};
        moleculeBox.reposition_atom(atoms[0]);
        CHECK(atoms[0].position == Coordinate2D{1, 0});
    }SECTION("Left Atom is repositioned correctly") {
        atoms[0].position = {-1, 0};
        moleculeBox.reposition_atom(atoms[0]);
        CHECK(atoms[0].position == Coordinate2D{4, 0});
    }SECTION("Above Atom is repositioned correctly") {
        atoms[0].position = {0, -1};
        moleculeBox.reposition_atom(atoms[0]);
        CHECK(atoms[0].position == Coordinate2D{0, 4});
    }SECTION("Below Atom is repositioned correctly") {
        atoms[0].position = {0, 6};
        moleculeBox.reposition_atom(atoms[0]);
        CHECK(atoms[0].position == Coordinate2D{0, 1});
    }


}


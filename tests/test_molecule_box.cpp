#include "MoleculeBox.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace Domain;
using Geometry::Coordinate2D;

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

TEST_CASE("Reposition All Atoms", "[MoleculeBox]") {
    Atom right = {{6, 0}, 0, 1};
    Atom left = {{-1, 0}, 0, 1};
    Atom above = {{0, -1}, 0, 1};
    Atom bellow = {{0, 6}, 0, 1};
    std::vector<Atom> atoms{right, left, above, bellow};
    MoleculeBox moleculeBox({{0, 0},
                             {5, 5}}, atoms);

    moleculeBox.reposition_atoms();


    CHECK(moleculeBox.atoms[0].position == Coordinate2D{1, 0});

    CHECK(moleculeBox.atoms[1].position == Coordinate2D{4, 0});

    CHECK(moleculeBox.atoms[2].position == Coordinate2D{0, 4});

    CHECK(moleculeBox.atoms[3].position == Coordinate2D{0, 1});


}

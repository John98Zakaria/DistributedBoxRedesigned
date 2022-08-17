//
// Created by jn98zk on 6/26/22.

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include "CuboidStructureCalc.hpp"

TEST_CASE("Calculates the anchors correctly", "[CuboidStructureCalc]") {
    using Geometry::CuboidStructureCalc;
    auto corners = CuboidStructureCalc::calculate_cuboid_corners(
            Geometry::CuboidPair{Coordinate3D<int>{0, 0, 0}, Coordinate3D<int>{3, 3, 3}});

    CHECK(corners[0] == Coordinate3D<int>{0, 0, 0});
    CHECK(corners[1] == Coordinate3D<int>{2, 0, 0});
    CHECK(corners[2] == Coordinate3D<int>{0, 2, 0});
    CHECK(corners[3] == Coordinate3D<int>{2, 2, 0});
    CHECK(corners[4] == Coordinate3D<int>{0, 0, 2});
    CHECK(corners[5] == Coordinate3D<int>{2, 0, 2});
    CHECK(corners[6] == Coordinate3D<int>{0, 2, 2});
    CHECK(corners[7] == Coordinate3D<int>{2, 2, 2});
}


TEST_CASE("Calculates the cuboid attributes correctly", "[CuboidStructureCalc]") {
    using Geometry::CuboidStructureCalc;
    auto attributes = CuboidStructureCalc::calculate_cuboid_attributes(
            Geometry::CuboidPair{Coordinate3D<int>{0, 0, 0}, Coordinate3D<int>{3, 3, 3}});

    std::cout << "Geometry::BOTTOM_LOWER_LEFT_CORNER = " << Geometry::BOTTOM_LOWER_LEFT_CORNER << std::endl;

    // <-----------------------CHECK CORNERS-------------------->
    REQUIRE(attributes[Geometry::BOTTOM_LOWER_LEFT_CORNER] ==
            Geometry::CuboidPair{Coordinate3D<int>{0, 0, 0}, Coordinate3D<int>{0, 0, 0} + Coordinate3D<int>{1, 1, 1}});
    REQUIRE(attributes[Geometry::BOTTOM_LOWER_RIGHT_CORNER] ==
            Geometry::CuboidPair{Coordinate3D<int>{2, 0, 0}, Coordinate3D<int>{2, 0, 0} + Coordinate3D<int>{1, 1, 1}});
    REQUIRE(attributes[Geometry::BOTTOM_UPPER_LEFT_CORNER] ==
            Geometry::CuboidPair{Coordinate3D<int>{0, 2, 0}, Coordinate3D<int>{0, 2, 0} + Coordinate3D<int>{1, 1, 1}});
    REQUIRE(attributes[Geometry::BOTTOM_UPPER_RIGHT_CORNER] ==
            Geometry::CuboidPair{Coordinate3D<int>{2, 2, 0}, Coordinate3D<int>{2, 2, 0} + Coordinate3D<int>{1, 1, 1}});
    REQUIRE(attributes[Geometry::TOP_LOWER_LEFT_CORNER] ==
            Geometry::CuboidPair{Coordinate3D<int>{0, 0, 2}, Coordinate3D<int>{0, 0, 2} + Coordinate3D<int>{1, 1, 1}});
    REQUIRE(attributes[Geometry::TOP_LOWER_RIGHT_CORNER] ==
            Geometry::CuboidPair{Coordinate3D<int>{2, 0, 2}, Coordinate3D<int>{2, 0, 2} + Coordinate3D<int>{1, 1, 1}});
    REQUIRE(attributes[Geometry::TOP_UPPER_LEFT_CORNER] ==
            Geometry::CuboidPair{Coordinate3D<int>{0, 2, 2}, Coordinate3D<int>{0, 2, 2} + Coordinate3D<int>{1, 1, 1}});
    REQUIRE(attributes[Geometry::TOP_UPPER_RIGHT_CORNER] ==
            Geometry::CuboidPair{Coordinate3D<int>{2, 2, 2}, Coordinate3D<int>{2, 2, 2} + Coordinate3D<int>{1, 1, 1}});
    // <-----------------------CHECK BOTTOM-------------------->
    CHECK(attributes[Geometry::BOTTOM_FACE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 0, 0}, Coordinate3D<int>{3, 3, 1}});
    CHECK(attributes[Geometry::BOTTOM_LOWER_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 0, 0}, Coordinate3D<int>{3, 1, 1}});
    CHECK(attributes[Geometry::BOTTOM_LEFT_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 0, 0}, Coordinate3D<int>{1, 3, 1}});
    CHECK(attributes[Geometry::BOTTOM_UPPER_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 2, 0}, Coordinate3D<int>{3, 3, 1}});
    CHECK(attributes[Geometry::BOTTOM_RIGHT_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{2, 0, 0}, Coordinate3D<int>{3, 3, 1}});

    // <-----------------------CHECK TOP-------------------->
    CHECK(attributes[Geometry::TOP_FACE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 0, 2}, Coordinate3D<int>{3, 3, 3}});
    CHECK(attributes[Geometry::TOP_LOWER_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 0, 2}, Coordinate3D<int>{3, 1, 3}});
    CHECK(attributes[Geometry::TOP_LEFT_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 0, 2}, Coordinate3D<int>{1, 3, 3}});
    CHECK(attributes[Geometry::TOP_UPPER_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 2, 2}, Coordinate3D<int>{3, 3, 3}});
    CHECK(attributes[Geometry::TOP_RIGHT_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{2, 0, 2}, Coordinate3D<int>{3, 3, 3}});
// <-----------------------CHECK LEFT-------------------->
    CHECK(attributes[Geometry::LEFT_FACE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 0, 0}, Coordinate3D<int>{1, 3, 3}});
    CHECK(attributes[Geometry::LEFT_LOWER_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 0, 0}, Coordinate3D<int>{1, 3, 1}});
    CHECK(attributes[Geometry::LEFT_LEFT_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 0, 0}, Coordinate3D<int>{1, 1, 3}});
    CHECK(attributes[Geometry::LEFT_UPPER_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 0, 2}, Coordinate3D<int>{1, 3, 3}});
    CHECK(attributes[Geometry::LEFT_RIGHT_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 2, 0}, Coordinate3D<int>{1, 3, 3}});
    // <-----------------------CHECK RIGHT-------------------->
    CHECK(attributes[Geometry::RIGHT_FACE] ==
          Geometry::CuboidPair{Coordinate3D<int>{2, 0, 0}, Coordinate3D<int>{3, 3, 3}});
    CHECK(attributes[Geometry::RIGHT_LOWER_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{2, 0, 0}, Coordinate3D<int>{3, 3, 1}});
    CHECK(attributes[Geometry::RIGHT_LEFT_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{2, 0, 0}, Coordinate3D<int>{3, 1, 3}});
    CHECK(attributes[Geometry::RIGHT_UPPER_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{2, 0, 2}, Coordinate3D<int>{3, 3, 3}});
    CHECK(attributes[Geometry::RIGHT_RIGHT_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{2, 2, 0}, Coordinate3D<int>{3, 3, 3}});

    // <-----------------------CHECK BACK-------------------->
    CHECK(attributes[Geometry::BACK_FACE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 0, 0}, Coordinate3D<int>{3, 1, 3}});

    CHECK(attributes[Geometry::BACK_LOWER_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 0, 0}, Coordinate3D<int>{3, 1, 1}});

    CHECK(attributes[Geometry::BACK_LEFT_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 0, 0}, Coordinate3D<int>{1, 1, 3}});

    CHECK(attributes[Geometry::BACK_UPPER_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 0, 2}, Coordinate3D<int>{3, 1, 3}});

    CHECK(attributes[Geometry::BACK_RIGHT_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{2, 0, 0}, Coordinate3D<int>{3, 1, 3}});




    // <-----------------------CHECK FRONT-------------------->
    CHECK(attributes[Geometry::FRONT_FACE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 2, 0}, Coordinate3D<int>{3, 3, 3}});
    CHECK(attributes[Geometry::FRONT_LOWER_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 2, 0}, Coordinate3D<int>{3, 3, 1}});
    CHECK(attributes[Geometry::FRONT_LEFT_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 2, 0}, Coordinate3D<int>{1, 3, 3}});
    CHECK(attributes[Geometry::FRONT_UPPER_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{0, 2, 2}, Coordinate3D<int>{3, 3, 3}});
    CHECK(attributes[Geometry::FRONT_RIGHT_EDGE] ==
          Geometry::CuboidPair{Coordinate3D<int>{2, 2, 0}, Coordinate3D<int>{3, 3, 3}});


}


TEST_CASE("NeighbourRelation can be converted to CuboidFeature","[CuboidFeature,NeighbourRelation]"){
    using namespace Geometry;
    CHECK(LEFT_FACE == cuboidFacefromNeighbourRelation(PLANE_CENTER_LEFT));
}
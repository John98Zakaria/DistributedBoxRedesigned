cmake_minimum_required(VERSION 3.22)
project(DistributedBoxRedesigned)

set(CMAKE_CXX_STANDARD 20)
find_package(spdlog REQUIRED)
find_package(HPX REQUIRED)

add_library(GEOMETRY src/Rectangle.cpp src/Coordinate2D.cpp src/PeriodicNeighbourCalculator.cpp)
add_library(Functional src/MoleculeBox.cpp include/MoleculeBox.hpp)
set_target_properties(GEOMETRY PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(GEOMETRY PUBLIC include)
target_link_libraries(GEOMETRY PUBLIC spdlog::spdlog)
target_link_libraries(Functional PUBLIC GEOMETRY)
target_include_directories(Functional PUBLIC include)

add_library(HPXCOM include/hpx_box_component)
set_target_properties(HPXCOM PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(HPXCOM HPX::hpx)


add_executable(DistributedBoxRedesigned main.cpp)
target_link_libraries(DistributedBoxRedesigned PUBLIC Functional HPXCOM HPX::hpx HPX::wrap_main HPX::iostreams_component)
add_subdirectory(tests)
cmake_minimum_required(VERSION 3.22)
project(DistributedBoxRedesigned)
find_package(Catch2 REQUIRED)

add_executable(test_cooridnates test_cooridnate.cpp)
target_link_libraries(test_cooridnates PRIVATE Catch2::Catch2WithMain GEOMETRY)
add_executable(test_rectangle test_rectangle.cpp)
target_link_libraries(test_rectangle PRIVATE Catch2::Catch2WithMain GEOMETRY)


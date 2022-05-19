cmake_minimum_required(VERSION 3.22)
project(DistributedBoxRedesigned)

set(CMAKE_CXX_STANDARD 17)

add_library(GEOMETRY src/Rectangle.cpp src/Coordinate2D.cpp)

set_target_properties(GEOMETRY PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(GEOMETRY PUBLIC include)
add_executable(DistributedBoxRedesigned main.cpp)
target_link_libraries(DistributedBoxRedesigned PRIVATE GEOMETRY)
find_package(Catch2 REQUIRED)
add_subdirectory(tests)
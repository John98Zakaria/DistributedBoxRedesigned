cmake_minimum_required(VERSION 3.22)
project(DistributedBoxRedesigned)

set(CMAKE_CXX_STANDARD 17)
find_package(spdlog REQUIRED HINTS /home/jn98zk/cpp_stuff/spdlog-1.10.0/installation/lib/cmake/spdlog)

add_library(GEOMETRY src/Rectangle.cpp src/Coordinate2D.cpp)
add_library(Functional src/MoleculeBox.cpp include/MoleculeBox.hpp)
set_target_properties(GEOMETRY PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(GEOMETRY PUBLIC include)
target_link_libraries(GEOMETRY PUBLIC spdlog::spdlog)
target_link_libraries(Functional PUBLIC GEOMETRY)
target_include_directories(Functional PUBLIC include)


add_executable(DistributedBoxRedesigned main.cpp)
target_link_libraries(DistributedBoxRedesigned PUBLIC Functional)
find_package(Catch2 REQUIRED)
add_subdirectory(tests)
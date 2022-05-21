#include <iostream>
#include "MoleculeBox.hpp"
#include "spdlog/sinks/basic_file_sink.h"

using namespace Geometry;
using namespace Domain;

int main() {

    auto logger = spdlog::basic_logger_mt("AtomLogger", "../basic-log.txt");
    Rectangle dims({0, 0}, {5, 5});
    Atom atom{{0, 0}, 1, {1, 0}};
    MoleculeBox box(dims, std::vector<Atom>{atom});
    MoleculeBox box2(dims, {Atom{{0, 0}, 1, {0, 1}}});
    for (size_t i = 0; i < 20; ++i) {
        box.step();
        logger->log(spdlog::level::info, box.getAtoms()[0]);
    }

    return 0;
}

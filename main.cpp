#include <iostream>
#include "Rectangle.hpp"

int main() {
    Rectangle rectangle({1,2},{4,5});
    auto w=rectangle.width();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

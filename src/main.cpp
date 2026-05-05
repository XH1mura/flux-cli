#include "cli.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        return CLI::handle(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}

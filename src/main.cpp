#include <iostream>
#include <string>

#include "lexer.h"

// command line calculator
// "2 + 2" -> 4
// one CLI argument : string
auto main(int argc, char* argv[]) -> int {
    if (argc != 2) {
        std::cerr << "Error: Invalid number of arguments\n";
        std::cout << "Usage: " << argv[0] << " \"<expression>\"\n";
        return 1;
    }

    std::string expression {argv[1]};

    auto tokens = lexer(expression);

    return 0;
}

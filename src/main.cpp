#include <iostream>
#include <string>

#include "ast.h"
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

    std::vector<ParseToken> tokens = lexer(expression);

    ASTNode* root = nullptr;
    auto res = ast_from_tokens(tokens, root);
    if (!res.has_value()) {
        std::cerr << "Error: " << res.error() << '\n';
        return 1;
    }

    std::cout << res.value()->show() << '\n';

    return 0;
}

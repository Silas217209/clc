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

    std::queue<ParseToken> rpn = to_reverse_polish(tokens);

    while (!rpn.empty()) {
        auto token = rpn.front();
        switch (token.type) {
            case TokenType::Number:
                std::cout << token.value;
                break;
            case TokenType::Plus:
                std::cout << "+";
                break;
            case TokenType::Minus:
                std::cout << "-";
                break;
            case TokenType::Multiply:
                std::cout << "*";
                break;
            case TokenType::Divide:
                std::cout << "/";
                break;
            case TokenType::LParen:
                std::cout << "(";
                break;
            case TokenType::RParen:
                std::cout << ")";
                break;
        }
        rpn.pop();
    }

    std::cout << "\n";

    return 0;
}

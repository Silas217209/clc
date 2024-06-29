#include <iostream>
#include <string>

#include "ast.h"
#include "lexer.h"

auto display_token(ParseToken token) -> std::string {
    switch (token.type) {
        case TokenType::Number:
            return " " + std::to_string(token.value);
        case TokenType::Plus:
            return "+";
        case TokenType::Minus:
            return "-";
        case TokenType::Multiply:
            return "*";
        case TokenType::Divide:
            return "/";
        case TokenType::LParen:
            return "(";
        case TokenType::RParen:
            return ")";
    }
}

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

    std::cout << "\n";

    auto ast_result = ast(tokens);
    if (!ast_result.has_value()) {
        std::cerr << "Error: " << ast_result.error() << "\n";
        return 1;
    }
    std::cout << ast_result.value()->show() << "\n";

    return 0;
}

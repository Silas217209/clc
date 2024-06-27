#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

enum class TokenType {
    Number,
    Plus,
    Minus,
    Multiply,
    Divide,
    LParen,
    RParen,
    End,
    Invalid
};

struct Token {
    TokenType type;
    size_t pos;
    size_t len;
};

auto lexer(std::string expression) -> std::vector<Token> {
    std::vector<Token> tokens;

    for (size_t i = 0; i < expression.size(); i++) {
        char c = expression[i];
        if (c == ' ') {
            continue;
        }

        std::cout << c << '\n';

        if (c == '+') {
            tokens.push_back({TokenType::Plus, i, 1});
            continue;
        }
        if (c == '-') {
            tokens.push_back({TokenType::Minus, i, 1});
            continue;
        }
        if (c == '*') {
            tokens.push_back({TokenType::Multiply, i, 1});
            continue;
        }
        if (c == '/') {
            tokens.push_back({TokenType::Divide, i, 1});
            continue;
        }
        if (c == '(') {
            tokens.push_back({TokenType::LParen, i, 1});
            continue;
        }
        if (c == ')') {
            tokens.push_back({TokenType::RParen, i, 1});
            continue;
        }
        std::string string_num;
        size_t start_pos = i;
        while (c >= '0' && c <= '9') {
            string_num.push_back(c);
            i++;
            c = expression[i];
        }
        tokens.push_back({TokenType::Number, start_pos, string_num.size()});
    }

    return tokens;
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

    auto tokens = lexer(expression);

    return 0;
}

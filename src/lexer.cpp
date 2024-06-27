#include "lexer.h"

#include <iostream>
#include <string>
#include <vector>

auto lexer(std::string expression) -> std::vector<ParseToken> {
    std::vector<ParseToken> tokens;

    for (size_t i = 0; i < expression.size(); i++) {
        char c = expression[i];
        if (c == ' ') {
            continue;
        }

        std::cout << c << '\n';

        if (c == '+') {
            tokens.push_back({TokenType::Plus, 0, i, 1});
            continue;
        }
        if (c == '-') {
            tokens.push_back({TokenType::Minus, 0, i, 1});
            continue;
        }
        if (c == '*') {
            tokens.push_back({TokenType::Multiply, 0, i, 1});
            continue;
        }
        if (c == '/') {
            tokens.push_back({TokenType::Divide, 0, i, 1});
            continue;
        }
        if (c == '(') {
            tokens.push_back({TokenType::LParen, 0, i, 1});
            continue;
        }
        if (c == ')') {
            tokens.push_back({TokenType::RParen, 0, i, 1});
            continue;
        }
        std::string string_num;
        size_t start_pos = i;
        while (c >= '0' && c <= '9') {
            string_num.push_back(c);
            i++;
            c = expression[i];
        }

        int val = std::stoi(string_num);
        tokens.push_back({TokenType::Number, val, start_pos, string_num.size()}
        );
    }

    return tokens;
}

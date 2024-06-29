#include "lexer.h"

#include <iostream>
#include <string>
#include <vector>

#include "expected.h"

auto lexer(std::string expression) -> tl::expected<std::vector<ParseToken>, std::string> {
    std::vector<ParseToken> tokens;

    for (size_t i = 0; i < expression.size(); i++) {
        bool is_float = false;

        char c = expression[i];
        if (c == ' ') {
            continue;
        }

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
        if (c == '^') {
            tokens.push_back({TokenType::Pow, 0, i, 1});
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
        while ((c >= '0' && c <= '9') || c == '.') {
            if (c == '.') {
                if (is_float) {
                    return tl::make_unexpected("Invalid Float");
                }
                is_float = true;
            }
            string_num.push_back(c);
            i++;
            c = expression[i];
        }
        i--;
        if (is_float) {
            double val = std::stod(string_num);
            tokens.push_back({TokenType::Number, val, start_pos, string_num.size()});

        } else {
            int val = std::stoi(string_num);
            tokens.push_back({TokenType::Number, static_cast<double>(val), start_pos, string_num.size()});
        }
    }

    return tokens;
}

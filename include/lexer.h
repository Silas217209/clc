#pragma once

#include <cstddef>
#include <queue>
#include <string>
#include <vector>
enum class TokenType { Number, Plus, Minus, Multiply, Divide, LParen, RParen };

struct ParseToken {
    TokenType type;
    int value;

    size_t pos;
    size_t len;
};

auto lexer(std::string expression) -> std::vector<ParseToken>;

auto to_reverse_polish(const std::vector<ParseToken>& tokens) -> std::queue<ParseToken>;

auto precedence(TokenType token_type) -> int;

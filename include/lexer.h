#pragma once

#include <cstddef>
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

struct ParseToken {
    TokenType type;
    int value = 0;
    size_t pos;
    size_t len;
};

auto lexer(std::string expression) -> std::vector<ParseToken>;

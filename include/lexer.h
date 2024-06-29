#pragma once

#include <cstddef>
#include <queue>
#include <string>
#include <vector>

#include "expected.h"
enum class TokenType { Number, Plus, Minus, Multiply, Divide, LParen, RParen };

struct ParseToken {
    TokenType type;
    int value;

    size_t pos;
    size_t len;
};

auto lexer(std::string expression) -> std::vector<ParseToken>;

auto precedence(TokenType token_type) -> int;

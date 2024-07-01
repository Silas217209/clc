#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "expected.h"

enum class TokenType { Number, Plus, Minus, UnaryMinus, Multiply, Divide, Pow, LParen, RParen };

struct ParseToken {
    TokenType type;
    double value;

    size_t pos;
    size_t len;
};

auto lexer(std::string expression) -> tl::expected<std::vector<ParseToken>, std::string>;

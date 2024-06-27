#pragma once

#include <vector>

#include "expected.h"
#include "lexer.h"
enum class ASTNodeType { Number, Plus, Minus, Multiply, Divide };

struct ASTNode {
    ASTNodeType type;
    int value = 0;
    ASTNode* right = nullptr;
    ASTNode* left = nullptr;
};

auto ast_from_tokens(std::vector<ParseToken> tokens) -> tl::expected<ASTNode, std::string>;

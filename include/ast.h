#pragma once

#include <string>
#include <vector>

#include "expected.h"
#include "lexer.h"

class ASTNode {
  public:
    virtual ~ASTNode() = default;
    virtual auto show() const -> std::string;
};

class ASTNumber: public ASTNode {
  public:
    ASTNumber(int value);
    int value;
    auto show() const -> std::string override;
};

class ASTPlus: public ASTNode {
  public:
    ASTPlus(ASTNode* left, ASTNode* right);
    ASTNode* right;
    ASTNode* left;
    auto show() const -> std::string override;
};

class ASTMinus: public ASTNode {
  public:
    ASTMinus(ASTNode* left, ASTNode* right);

    ASTNode* right;
    ASTNode* left;
    auto show() const -> std::string override;
};

class ASTMultiply: public ASTNode {
  public:
    ASTMultiply(ASTNode* left, ASTNode* right);
    ASTNode* right;
    ASTNode* left;
    auto show() const -> std::string override;
};

class ASTDivide: public ASTNode {
  public:
    ASTDivide(ASTNode* left, ASTNode* right);
    ASTNode* right;
    ASTNode* left;
    auto show() const -> std::string override;
};

class ASTNegate: public ASTNode {
  public:
    ASTNegate(ASTNode* val);
    ASTNode* val;
    auto show() const -> std::string override;
};

auto ast_from_tokens(std::vector<ParseToken> tokens, ASTNode* node) -> tl::expected<ASTNode*, std::string>;

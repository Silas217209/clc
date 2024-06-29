#pragma once

#include <string>
#include <vector>

#include "expected.h"
#include "lexer.h"

class ASTNode {
  public:
    virtual ~ASTNode() = default;
    virtual auto show() const -> std::string = 0;
    virtual auto eval() -> double = 0;
};

class ASTNumber: public ASTNode {
  public:
    ASTNumber(double value);
    double value;
    auto show() const -> std::string override;
    auto eval() -> double override;
};

class ASTPlus: public ASTNode {
  public:
    ASTPlus(ASTNode* left, ASTNode* right);
    ASTNode* right;
    ASTNode* left;
    auto show() const -> std::string override;
    auto eval() -> double override;
};

class ASTMinus: public ASTNode {
  public:
    ASTMinus(ASTNode* left, ASTNode* right);

    ASTNode* right;
    ASTNode* left;
    auto show() const -> std::string override;
    auto eval() -> double override;
};

class ASTMultiply: public ASTNode {
  public:
    ASTMultiply(ASTNode* left, ASTNode* right);
    ASTNode* right;
    ASTNode* left;
    auto show() const -> std::string override;
    auto eval() -> double override;
};

class ASTDivide: public ASTNode {
  public:
    ASTDivide(ASTNode* left, ASTNode* right);
    ASTNode* right;
    ASTNode* left;
    auto show() const -> std::string override;
    auto eval() -> double override;
};

class ASTNegate: public ASTNode {
  public:
    ASTNegate(ASTNode* val);
    ASTNode* val;
    auto show() const -> std::string override;
    auto eval() -> double override;
};

class ASTPow: public ASTNode {
  public:
    ASTPow(ASTNode* base, ASTNode* exponent);
    ASTNode* base;
    ASTNode* exponent;
    auto show() const -> std::string override;
    auto eval() -> double override;
};

auto precedence(TokenType type) -> int;

auto ast(const std::vector<ParseToken>& tokens) -> tl::expected<ASTNode*, std::string>;

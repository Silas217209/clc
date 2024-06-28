#include "ast.h"

#include <expected>
#include <string>
#include <vector>

#include "expected.h"
#include "lexer.h"

ASTNumber::ASTNumber(int value) : value(value) {}

ASTPlus::ASTPlus(ASTNode* left, ASTNode* right) : left(left), right(right) {}

ASTMinus::ASTMinus(ASTNode* left, ASTNode* right) : left(left), right(right) {}

ASTMultiply::ASTMultiply(ASTNode* left, ASTNode* right) : left(left), right(right) {}

ASTDivide::ASTDivide(ASTNode* left, ASTNode* right) : left(left), right(right) {}

ASTNegate::ASTNegate(ASTNode* val) : val(val) {}

auto ASTNumber::show() const -> std::string {
    return std::to_string(value);
}

auto ASTPlus::show() const -> std::string {
    return "(" + left->show() + " + " + right->show() + ")";
}

auto ASTMinus::show() const -> std::string {
    return "(" + left->show() + " - " + right->show() + ")";
}

auto ASTMultiply::show() const -> std::string {
    return "(" + left->show() + " * " + right->show() + ")";
}

auto ASTDivide::show() const -> std::string {
    return "(" + left->show() + " / " + right->show() + ")";
}

auto ASTNegate::show() const -> std::string {
    return "(-" + val->show() + ")";
}

auto ast_from_tokens(std::vector<ParseToken> tokens, ASTNode* node) -> tl::expected<ASTNode*, std::string> {
    for (size_t i = 0; i < tokens.size(); i++) {
        ParseToken token = tokens[i];

        switch (token.type) {
            case TokenType::Number: {
                ASTNumber* number = new ASTNumber(token.value);
                if (node != nullptr) {
                    return tl::make_unexpected("Error: Number token with left side");
                }

                node = number;
                break;
            }
            case TokenType::Plus: {
                if (node == nullptr) {
                    return tl::make_unexpected("Error: Plus token with no left side");
                }
                ASTNode* right = nullptr;
                auto res = ast_from_tokens(std::vector(tokens.begin() + i + 1, tokens.end()), right);
                if (!res.has_value()) {
                    return tl::make_unexpected(res.error());
                }

                return new ASTPlus(node, res.value());

                break;
            }
            case TokenType::Minus: {
                if (node == nullptr) {
                    return tl::make_unexpected("Error: Minus token with no left side");
                }
                ASTNode* right = nullptr;
                auto res = ast_from_tokens(std::vector(tokens.begin() + i + 1, tokens.end()), right);
                if (!res.has_value()) {
                    return tl::make_unexpected(res.error());
                }

                // if right node is an operator
                if (auto plusNode = dynamic_cast<ASTPlus*>(right)) {
                    auto temp_right = plusNode->right;
                    plusNode->right = node;
                    ASTPlus* new_plus = new ASTPlus(new ASTNegate(plusNode->left);
                } else if (auto minusNode = dynamic_cast<ASTMinus*>(right)) {
                }

                return new ASTMinus(node, res.value());

                break;
            }
            case TokenType::Multiply: {
                if (node == nullptr) {
                    return tl::make_unexpected("Error: Minus token with no left side");
                }
                ASTNode* right = nullptr;
                auto res = ast_from_tokens(std::vector(tokens.begin() + i + 1, tokens.end()), right);
                if (!res.has_value()) {
                    return tl::make_unexpected(res.error());
                }

                return new ASTMultiply(node, res.value());

                break;
            }
            case TokenType::Divide: {
                if (node == nullptr) {
                    return tl::make_unexpected("Error: Minus token with no left side");
                }
                ASTNode* right = nullptr;
                auto res = ast_from_tokens(std::vector(tokens.begin() + i + 1, tokens.end()), right);
                if (!res.has_value()) {
                    return tl::make_unexpected(res.error());
                }

                return new ASTDivide(node, res.value());

                break;
            }
            case TokenType::LParen:
            case TokenType::RParen:
            case TokenType::End:
            case TokenType::Invalid:
                break;
        }
    }

    return node;
}

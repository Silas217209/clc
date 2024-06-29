#include "ast.h"

#include <expected>
#include <stack>
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

auto ASTNumber::eval() -> int {
    return value;
}

auto ASTPlus::eval() -> int {
    return left->eval() + right->eval();
}

auto ASTMinus::eval() -> int {
    return left->eval() - right->eval();
}

auto ASTMultiply::eval() -> int {
    return left->eval() * right->eval();
}

auto ASTDivide::eval() -> int {
    return left->eval() / right->eval();
}

auto ASTNegate::eval() -> int {
    return -val->eval();
}

// Shunting Yard Algorithm
auto ast(const std::vector<ParseToken>& tokens) -> tl::expected<ASTNode*, std::string> {
    std::stack<ParseToken> operators;
    std::stack<ASTNode*> output;

    for (ParseToken token : tokens) {
        switch (token.type) {
            case TokenType::Number: {
                output.push(new ASTNumber(token.value));
                break;
            }
            case TokenType::Plus:
            case TokenType::Minus:
            case TokenType::Multiply:
            case TokenType::Divide: {
                while (!operators.empty() && precedence(operators.top().type) >= precedence(token.type)) {
                    auto right = output.top();
                    output.pop();
                    auto left = output.top();
                    output.pop();

                    ASTNode* op;
                    switch (operators.top().type) {
                        case TokenType::Plus:
                            op = new ASTPlus(left, right);
                            break;
                        case TokenType::Minus:
                            op = new ASTMinus(left, right);
                            break;
                        case TokenType::Multiply:
                            op = new ASTMultiply(left, right);
                            break;
                        case TokenType::Divide:
                            op = new ASTDivide(left, right);
                            break;
                        default:
                            return tl::make_unexpected("Invalid operator");
                    }

                    output.push(op);
                    operators.pop();
                }
                operators.push(token);
                break;
            }
            case TokenType::LParen: {
                operators.push(token);
                break;
            }
            case TokenType::RParen: {
                while (!operators.empty() && operators.top().type != TokenType::LParen) {
                    auto right = output.top();
                    output.pop();
                    auto left = output.top();
                    output.pop();

                    ASTNode* op;
                    switch (operators.top().type) {
                        case TokenType::Plus:
                            op = new ASTPlus(left, right);
                            break;
                        case TokenType::Minus:
                            op = new ASTMinus(left, right);
                            break;
                        case TokenType::Multiply:
                            op = new ASTMultiply(left, right);
                            break;
                        case TokenType::Divide:
                            op = new ASTDivide(left, right);
                            break;
                        default:
                            return tl::make_unexpected("Invalid operator");
                    }

                    output.push(op);
                    operators.pop();
                }
                // discard left bracket
                if (operators.empty()) {
                    return tl::make_unexpected("Mismatched parentheses");
                }
                operators.pop();
                break;
            }
        }
    }

    while (!operators.empty()) {
        auto right = output.top();
        output.pop();
        auto left = output.top();
        output.pop();
        switch (operators.top().type) {
            case TokenType::Plus:
                output.push(new ASTPlus(left, right));
                break;
            case TokenType::Minus:
                output.push(new ASTMinus(left, right));
                break;
            case TokenType::Multiply:
                output.push(new ASTMultiply(left, right));
                break;
            case TokenType::Divide:
                output.push(new ASTDivide(left, right));
                break;
            default:
                return tl::make_unexpected("Invalid operator");
        }
        operators.pop();
    }

    if (output.size() != 1) {
        return tl::make_unexpected("Invalid expression, size is " + std::to_string(output.size()) + " expected 1");
    }

    return output.top();
}

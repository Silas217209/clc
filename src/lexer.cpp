#include "lexer.h"

#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "expected.h"

auto lexer(std::string expression) -> std::vector<ParseToken> {
    std::vector<ParseToken> tokens;

    for (size_t i = 0; i < expression.size(); i++) {
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
        while (c >= '0' && c <= '9') {
            string_num.push_back(c);
            i++;
            c = expression[i];
        }
        i--;

        int val = std::stoi(string_num);
        tokens.push_back({TokenType::Number, val, start_pos, string_num.size()});
    }

    return tokens;
}

auto precedence(TokenType type) -> int {
    switch (type) {
        case TokenType::Plus:
        case TokenType::Minus:
            return 1;
        case TokenType::Multiply:
        case TokenType::Divide:
            return 2;
        default:
            return 0;
    }
}

// Shunting Yard Algorithm
auto to_reverse_polish(const std::vector<ParseToken>& tokens) -> tl::expected<std::queue<ParseToken>, std::string> {
    std::stack<ParseToken> operators;
    std::queue<ParseToken> output;

    for (ParseToken token : tokens) {
        switch (token.type) {
            case TokenType::Number: {
                output.push(token);
                break;
            }
            case TokenType::Plus:
            case TokenType::Minus:
            case TokenType::Multiply:
            case TokenType::Divide: {
                while (!operators.empty() && precedence(operators.top().type) >= precedence(token.type)) {
                    output.push(operators.top());
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
                    output.push(operators.top());
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
        output.push(operators.top());
        operators.pop();
    }

    return output;
}

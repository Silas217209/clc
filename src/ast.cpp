#include "ast.h"

#include <expected>
#include <string>
#include <vector>

#include "expected.h"
#include "lexer.h"

auto ast_from_tokens(std::vector<ParseToken> tokens
) -> tl::expected<ASTNode, std::string> {
    for (size_t i = 0; i < tokens.size(); i++) {
        if (i == 0) {
            // if first token is operator, invalid
            switch (tokens[i].type) {
                case TokenType::Plus:
                case TokenType::Minus:
                case TokenType::Multiply:
                case TokenType::Divide:
                    // error

                    break;
                default:
                    break;
            }
        }
    }
}

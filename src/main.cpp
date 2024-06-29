#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

#include "ast.h"
#include "lexer.h"

auto display_token(ParseToken token) -> std::string {
    switch (token.type) {
        case TokenType::Number:
            return " " + std::to_string(token.value);
        case TokenType::Plus:
            return "+";
        case TokenType::Minus:
            return "-";
        case TokenType::Multiply:
            return "*";
        case TokenType::Divide:
            return "/";
        case TokenType::Pow:
            return "^";
        case TokenType::LParen:
            return "(";
        case TokenType::RParen:
            return ")";
    }
}

// continued fraction approximation
auto fraction_approximation(double value, double tolerance = 1e-15) -> std::string {
    // Edge case for zero
    if (value == 0.0)
        return "0/1";

    if (value == 1.0)
        return "1/1";

    double decimal = value - std::floor(value);

    // Initial values for the Farey sequence (0/1 and 1/1)
    int a = 0, b = 1;  // left fraction: a/b
    int c = 1, d = 1;  // right fraction: c/d

    // Continued fraction approximation
    while (true) {
        // Compute the mediant
        int mediant_numerator = a + c;
        int mediant_denominator = b + d;

        // Check if we are within the tolerance
        double mediant_value = static_cast<double>(mediant_numerator) / mediant_denominator;
        if (std::abs(mediant_value - decimal) < tolerance) {
            return std::to_string(mediant_numerator + static_cast<int>(value) * mediant_denominator) + "/"
                + std::to_string(mediant_denominator);
        }

        // Update the Farey sequence bounds
        if (decimal > mediant_value) {
            a = mediant_numerator;
            b = mediant_denominator;
        } else {
            c = mediant_numerator;
            d = mediant_denominator;
        }
    }
}

// command line calculator
// "2 + 2" -> 4
// one CLI argument : string
auto main(int argc, char* argv[]) -> int {
    if (argc != 2) {
        std::cerr << "Error: Invalid number of arguments\n";
        std::cout << "Usage: " << argv[0] << " \"<expression>\"\n";
        return 1;
    }

    std::string expression {argv[1]};

    tl::expected<std::vector<ParseToken>, std::string> tokens = lexer(expression);
    if (!tokens.has_value()) {
        std::cerr << "Error: " << tokens.error() << "\n";
        return 1;
    }

    std::cout << "\n";

    auto ast_result = ast(tokens.value());
    if (!ast_result.has_value()) {
        std::cerr << "Error: " << ast_result.error() << "\n";
        return 1;
    }

    double result = ast_result.value()->eval();

    if (std::floor(result) == result) {
        std::cout << expression << " = " << result << "\n";
    } else {
        std::cout << expression << " = " << fraction_approximation(result) << " = " << result << "\n";
    }

    return 0;
}

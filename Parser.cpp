#include "Parser.hpp"

Parser::Parser(const std::pair<std::string, std::vector<std::variant<int, bool>>>& input) {
    if (input.first == "ADD") {
        add(input.second);
    }
    else if (input.first == "SUB") {
        subtract(input.second);
    }
    else if (input.first == "MULT") {
        multiply(input.second);
    }
    else if (input.first == "DIV") {
        divide(input.second);
    }
    else if (input.first == "POW") {
        power(input.second);
    }
    else if (input.first == "MOD") {
        modulus(input.second);
    }
    else if (input.first == "AND") {
        booleanAnd(input.second);
    }
    else if (input.first == "NOT") {
        booleanNot(input.second);
    }
    else if (input.first == "OR") {
        booleanOr(input.second);
    }
}

void Parser::add(const std::vector<std::variant<int, bool>>& operands) noexcept {
    for (auto& element : operands) {
        if (std::holds_alternative<int>(element)) {
            result += std::get<int>(element);
        }
    }
}

void Parser::subtract(const std::vector<std::variant<int, bool>>& operands)  noexcept {
    result = std::get<int>(operands[0]) - std::get<int>(operands[1]);
}

void Parser::multiply(const std::vector<std::variant<int, bool>>& operands) noexcept {
    result = 1.0;
    for (auto& element : operands) {
        if (std::holds_alternative<int>(element)) {
            result *= std::get<int>(element);
        }
    }
}

void Parser::divide(const std::vector<std::variant<int, bool>>& operands) {
    if (std::get<int>(operands[1]) == 0) {
        throw std::invalid_argument("Division by zero");
    }
    result = static_cast<double>(std::get<int>(operands[0])) / static_cast<double>(std::get<int>(operands[1]));
}

void Parser::power(const std::vector<std::variant<int, bool>>& operands) {
    int base = std::get<int>(operands[0]);
    int exponent = std::get<int>(operands[1]);
    result = std::pow(base, exponent);
}

void Parser::modulus(const std::vector<std::variant<int, bool>>& operands) {
    if (std::get<int>(operands[1]) == 0) {
        throw std::invalid_argument("Division by zero");
    }
    result = std::get<int>(operands[0]) % std::get<int>(operands[1]);
}

void Parser::booleanAnd(const std::vector<std::variant<int, bool>>& operands) noexcept {
    result = std::get<bool>(operands[0]) && std::get<bool>(operands[1]);
}

void Parser::booleanNot(const std::vector<std::variant<int, bool>>& operands) noexcept {
    result = !std::get<bool>(operands[0]);
}

void Parser::booleanOr(const std::vector<std::variant<int, bool>>& operands) noexcept {
    result = std::get<bool>(operands[0]) || std::get<bool>(operands[1]);
}

double Parser::getResult() const noexcept {
    return result;
}
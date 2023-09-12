#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <variant>
#include <cmath>
#include <stdexcept>

class Parser {
public:
    Parser(const std::pair<std::string, std::vector<std::variant<int, bool>>>& input);

    double getResult() const noexcept;

private:
    double result = 0.0;

    void add(const std::vector<std::variant<int, bool>>& operands) noexcept;
    void subtract(const std::vector<std::variant<int, bool>>& operands) noexcept;
    void multiply(const std::vector<std::variant<int, bool>>& operands) noexcept;
    void divide(const std::vector<std::variant<int, bool>>& operands);
    void power(const std::vector<std::variant<int, bool>>& operands);
    void modulus(const std::vector<std::variant<int, bool>>& operands);
    void booleanAnd(const std::vector<std::variant<int, bool>>& operands) noexcept;
    void booleanNot(const std::vector<std::variant<int, bool>>& operands) noexcept;
    void booleanOr(const std::vector<std::variant<int, bool>>& operands) noexcept;
};


#endif
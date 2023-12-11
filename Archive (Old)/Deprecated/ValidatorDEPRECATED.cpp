#include "Validator.hpp"

Validator::Validator(const std::vector<std::string>& input) {
    valid = checkCommand(input[0]) && checkOperands(input, input[0]);
}

bool Validator::checkCommand(const std::string& command) const noexcept {
    return commands.find(command) != commands.end();
}

bool Validator::checkOperatorFlags(const std::vector<std::string>& input) const noexcept {
    bool containsOps = false;
    bool containsOp1 = false;
    bool containsOp2 = false;
    for (size_t i = 1; i < input.size(); i++) {
        if (operators.find(input[i]) != operators.end()) {
            if (input[i] == "-ops") {
                if (containsOps) {
                    return false;
                }
                containsOps = true;
            }
            else if (input[i] == "-op1") {
                if (containsOp1) {
                    return false;
                }
                containsOp1 = true;
                if (i + 1 >= input.size() || operators.find(input[i + 1]) != operators.end()) {
                    return false;
                } // if the next token is an operator => it's not an operand
                i++;
            }
            else if (input[i] == "-op2") {
                if (containsOp2) {
                    return false;
                }
                containsOp2 = true;
                if (i + 1 >= input.size() || operators.find(input[i + 1]) != operators.end()) {
                    return false;
                }
                i++;
            }
        }
    }
    return containsOps || (containsOp1 && containsOp2);
}

bool Validator::checkOperands(const std::vector<std::string>& input, const std::string& command) const noexcept {
    if (binaryOperators.find(command) != binaryOperators.end()) {
        if (input.size() != 5) {
            return false;
        }
        if (input[1] != "-op1" || input[3] != "-op2") {
            return false;
        }
    }
    else if (booleanOperators.find(command) != booleanOperators.end()) {
        if (input.size() != 5) {
            return false;
        }
        if (input[1] != "-op1" || input[3] != "-op2") {
            return false;
        }
        if (input[2] != "True" && input[2] != "False") {
            return false;
        }
        if (input[4] != "True" && input[4] != "False") {
            return false;
        }
    }
    else {
        bool containsOps = false;
        for (size_t i = 1; i < input.size(); i++) {
            if (operators.find(input[i]) != operators.end()) {
                if (input[i] == "-ops") {
                    containsOps = true;
                }
            }
            else {
                try {
                    std::stoi(input[i]);
                }
                catch (const std::invalid_argument&) {
                    return false;
                }
            }
        }
        if (!containsOps && input.size() < 3) {
            return false;
        }
    }
    return true;
}

bool Validator::isValid() const noexcept {
    return valid;
}
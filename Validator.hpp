#include <vector>
#include <string>
#include <unordered_set>
#include <stdexcept>

class Validator {
public:
    Validator(const std::vector<std::string>& input);

    bool isValid() const noexcept;

private:
    bool valid = false;

    std::unordered_set<std::string> commands = {
        "ADD", "SUB", "MULT", "DIV", "POW", "AND", "NOT", "OR", "MOD"
    };

    std::unordered_set<std::string> binaryOperators = {
        "POW", "SUB", "DIV"
    };

    std::unordered_set<std::string> booleanOperators = {
        "AND", "NOT", "OR"
    };

    std::unordered_set<std::string> operators = {
        "-ops", "-op1", "-op2"
    };

    bool checkCommand(const std::string& command) const noexcept;
    bool checkOperatorFlags(const std::vector<std::string>& input) const noexcept;
    bool checkOperands(const std::vector<std::string>& input, const std::string& command) const noexcept;
};


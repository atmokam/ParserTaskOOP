#include "Tokenizer.hpp"


void Tokenizer::tokenize(const std::vector<std::string>& input) {
    std::unordered_set<std::string> commands = {
        "ADD", "SUB", "MULT", "DIV", "POW", "MOD", "AND", "NOT", "OR" "EXIT"
    };

    std::unordered_set<std::string> operators = {
        "-ops", "-op1", "-op2"
    };

    for (auto& token : input) {
        if (commands.find(token) != commands.end()) {
            tokenGotten.first = token;
        }
        else if (operators.find(token) == operators.end()) {
            tokenGotten.second.push_back(std::stoi(token));
        }
    }

}


Tokenizer::Tokenizer(const std::vector<std::string>& arg) {
    tokenize(arg);
}


std::pair<std::string, std::vector<int>> Tokenizer::getTokens() const noexcept {
    return tokenGotten;
}
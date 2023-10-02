#include "Tokenizer.hpp"


void Tokenizer::tokenize(const std::vector<std::string>& input) {
    std::unordered_set<std::string> commands = {
        "ADD", "SUB", "MULT", "DIV", "POW", "MOD", "AND", "NOT", "OR" 
    };

    std::unordered_set<std::string> operators = {
        "-ops", "-op1", "-op2"
    };

    for (auto& token : input) {
        if (commands.find(token) != commands.end()) {
            tokenGotten.first = token;
        }
        else if (operators.find(token) == operators.end()) {
            if (token == "True") {
                tokenGotten.second.push_back(true);
            }
            else if (token == "False") {
                tokenGotten.second.push_back(false);
            }
            else {
                tokenGotten.second.push_back(std::stoi(token));
            }
        }
    }

}


Tokenizer::Tokenizer(const std::vector<std::string>& arg) {
    tokenize(arg);
}


std::pair<std::string, std::vector<std::variant<int, bool>>> Tokenizer::getTokens() const noexcept {
    return tokenGotten;
}
#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

class Tokenizer {
private:
    std::pair<std::string, std::vector<int>> tokenGotten; // operators and operands
public:
    Tokenizer(std::istringstream iss);
    Tokenizer(const std::vector<std::string>& arg);
    void tokenize(const std::vector<std::string>& input);
    
    std::pair<std::string, std::vector<int>> getTokens() const noexcept;
};

#endif
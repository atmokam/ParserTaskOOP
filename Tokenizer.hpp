#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <variant>

class Tokenizer {
private:
    std::pair<std::string, std::vector<std::variant<int, bool>>> tokenGotten; // operators and operands
public:
    Tokenizer(std::istringstream iss);
    Tokenizer(const std::vector<std::string>& arg);
    ~Tokenizer() = default;
    void tokenize(const std::vector<std::string>& input);
    
    std::pair<std::string, std::vector<std::variant<int, bool>>> getTokens() const noexcept;
};

#endif
#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <variant>

class Tokenizer {
public:
    Tokenizer(std::string text);
    ~Tokenizer() = default;
    std::string tokenize();
};

#endif
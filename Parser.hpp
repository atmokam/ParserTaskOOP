#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <stdexcept>
#include "SyntaxValidator.hpp"

class Parser {
private:
    std::vector<std::string> tokens;
public:
    Parser(std::vector<std::string> tokensGotten);
    ~Parser() = default;
    void parse(); // CommandAST
};


#endif
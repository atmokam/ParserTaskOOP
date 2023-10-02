#include "Parser.hpp"


Parser::Parser(std::vector<std::string> tokensGotten) : tokens(tokensGotten) {}

// TODO: implement parse() method
void Parser::parse() {
    SyntaxValidator syntaxValidator(tokens);
    syntaxValidator.validate();
    if(!syntaxValidator.isValid()) {
        throw std::invalid_argument("Invalid syntax.");
    }

    

}
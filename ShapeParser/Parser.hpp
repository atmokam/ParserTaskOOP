#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <iostream>
#include <memory>
#include <vector>

#include "Command.hpp"
#include "Validator.hpp"
#include "Document.hpp"


class Parser {

    std::shared_ptr<Command> createCommand(std::string input);
    std::string commandName = "", prevOperand = "", prevToken = ""; 
    std::shared_ptr<Command> command = nullptr;
    //std::shared_ptr<Document> document = nullptr;
    
public:
    Parser() = default;
    void parse(std::string token);
    void reset();
    std::shared_ptr<Command> getCommand() const;
};

#endif
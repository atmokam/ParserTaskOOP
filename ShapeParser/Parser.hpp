#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <iostream>
#include <memory>
#include <vector>

#include "Command.hpp"
#include "Accumulator.hpp"
#include "Validator.hpp"


class Parser {

    std::unique_ptr<Command> createCommand(std::string input);
    std::string commandName = "", prevOperand = "", prevToken = "";
public:
    std::unique_ptr<Command> command = nullptr;
    Parser();
    void parse(std::string token);
    void reset();
};

#endif
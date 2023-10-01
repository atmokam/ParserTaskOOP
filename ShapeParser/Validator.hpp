#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <string>
#include <vector>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include "Command.hpp"


class Validator {

    static std::unordered_set<std::string> commands ;
    static std::unordered_map<std::string, std::vector<std::string>> validOperands;
    static std::unordered_set<std::string> shapes;

    static bool isID(std::string inputToBeChecked);
    static bool isPosition(std::string inputToBeChecked);
    static bool isHex(std::string inputToBeChecked);
    static bool isRadius(std::string inputToBeChecked);
    static bool isPath(std::string inputToBeChecked);


public:
    static bool isName(std::string inputToBeChecked);
    static bool isOperand(std::string inputToBeChecked, std::string commandName);
    static bool isValue(std::string inputToBeChecked, std::string operandName);
    static bool validateCommand(std::unique_ptr<Command> commandToBeChecked);
};


#endif
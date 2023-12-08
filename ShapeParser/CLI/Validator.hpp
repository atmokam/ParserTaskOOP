#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <string>
#include <vector>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <tuple>


class Command;


class Validator {

    std::unordered_map<std::string, std::unordered_map<std::string, int>> valids;
    std::unordered_set<std::string> shapes;
    std::unordered_set<std::string> styles;

    bool checkOperandQuantity(const std::shared_ptr<Command>& commandToBeChecked);
    std::unordered_map<std::string, std::vector<std::string>> mandatoryOperands;
    
    bool checkMandatoryOperands(const std::shared_ptr<Command>& commandToBeChecked);


    bool isID(const std::string& inputToBeChecked);
    bool isDouble(const std::string& inputToBeChecked);
    bool isHex(const std::string& inputToBeChecked);
    bool isInteger(const std::string& inputToBeChecked);
    bool isPath(const std::string& inputToBeChecked);
    bool isFilename(const std::string& inputToBeChecked);
    bool isStyle(const std::string& inputToBeChecked);


public:
    Validator();
    bool isName(const std::string& inputToBeChecked);
    bool isOperand(const std::string& inputToBeChecked, const std::string& commandName);
    bool isValue(const std::string& inputToBeChecked, const std::string& operandName);
    bool validateCommand(const std::shared_ptr<Command>& commandToBeChecked);
};


#endif
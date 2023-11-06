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
    static std::unordered_set<std::string> styles;

    // quantity checking
    static std::unordered_map<std::string, size_t> addValidOperands;
    static std::unordered_map<std::string, size_t> removeValidOperands;
    static std::unordered_map<std::string, size_t> changeValidOperands;
    static std::unordered_map<std::string, size_t> displayValidOperands;    
    static std::unordered_map<std::string, size_t> saveValidOperands;
    static std::unordered_map<std::string, size_t> loadValidOperands;

    static bool checkOperandQuantity(std::unordered_map<std::string, std::vector<std::string>> commandOperands, std::unordered_map<std::string, size_t> validOperands);
    
    static std::unordered_set<std::string> addShapeMandatoryOperands;
    static std::unordered_set<std::string> addSlideMandatoryOperands;
    static std::unordered_set<std::string> removeIDMandatoryOperands;
    static std::unordered_set<std::string> removeSlideMandatoryOperands;
    static std::unordered_set<std::string> changeMandatoryOperands;
    static std::unordered_set<std::string> displayMandatoryOperands;
    static std::unordered_set<std::string> saveMandatoryOperands;
    static std::unordered_set<std::string> loadMandatoryOperands;
    
    static bool checkMandatoryOperands(std::unordered_map<std::string, std::vector<std::string>> commandOperands, std::unordered_set<std::string> validOperands);


    static bool isID(const std::string& inputToBeChecked);
    static bool isDouble(const std::string& inputToBeChecked);
    static bool isHex(const std::string& inputToBeChecked);
    static bool isInteger(const std::string& inputToBeChecked);
    static bool isPath(const std::string& inputToBeChecked);
    static bool isFilename(const std::string& inputToBeChecked);
    static bool isStyle(const std::string& inputToBeChecked);


public:
    static bool isName(const std::string& inputToBeChecked);
    static bool isOperand(const std::string& inputToBeChecked, const std::string& commandName);
    static bool isValue(const std::string& inputToBeChecked, const std::string& operandName);
    static bool validateCommand(const std::shared_ptr<Command>& commandToBeChecked);
};


#endif
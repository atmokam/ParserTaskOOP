#include <algorithm>
#include <fstream>
#include "CLI/Validator.hpp"
#include "Command.hpp"


// general checking
// [TK] Extra unnnecessary vector, the map below already contains commands info
std::unordered_set<std::string> Validator::commands = {
        "add", "remove", "change", "display", "list", "save", "load", "next", "prev", "undo", "redo"
    };

std::unordered_map<std::string, std::vector<std::string>> Validator::validOperands = {
        {"add", {"-name", "-pos", "-lcolor", "-fcolor", "-w", "-h", "-slide", "-lwidth", "-lstyle"}},
        {"remove", {"-id", "-slide"}},
        {"change", {"-id", "-name", "-pos", "-lcolor", "-fcolor", "-w", "-h", "-lwidth", "-lstyle"}},
        {"display", {"-id"}},
        {"list", {}},
        {"save", {"-path", "-filename"}},
        {"load", {"-path"}}, 
        {"next", {}}, 
        {"prev", {}},
        {"undo", {}},
        {"redo", {}}
    };
// list of shapes should be obtained from the shape library
std::unordered_set<std::string> Validator::shapes = {
        "trapezoid", "rectangle", "line", "triangle", "ellipse"
    };

std::unordered_set<std::string> Validator::styles = {
    "solid", "dashed", "dotted"
    };




// operand quantity checking: 0 means no value, -1 means any number of values
std::unordered_map<std::string, size_t> Validator::addValidOperands = {
        {"-name", 1}, {"-lcolor", 1}, {"-fcolor", 1}, {"-pos", -1}, {"-w", 1}, {"-h", 1}, {"-slide", 0}, {"-lwidth", 1}, {"-lstyle", 1}
    };

std::unordered_map<std::string, size_t> Validator::removeValidOperands = {
        {"-id", 1}, {"-slide", 0}
    };

std::unordered_map<std::string, size_t> Validator::changeValidOperands = {
        {"-id", 1}, {"-name", 1}, {"-pos", -1}, {"-lcolor", 1}, {"-fcolor", 1}, {"-w", 1}, {"-h", 1}
    };

std::unordered_map<std::string, size_t> Validator::displayValidOperands = {
        {"-id", 1} 
    };

std::unordered_map<std::string, size_t> Validator::saveValidOperands = {
        {"-path", 1},
        {"-filename", 1}
    };

std::unordered_map<std::string, size_t> Validator::loadValidOperands = {
        {"-path", 1}
    };



// mandatory operand checking
std::unordered_set<std::string> Validator::addShapeMandatoryOperands = {
        "-name", "-pos", "-w", "-h"
    };

std::unordered_set<std::string> Validator::addSlideMandatoryOperands = {
        "-slide"
    };

std::unordered_set<std::string> Validator::removeIDMandatoryOperands = {
        "-id"
    };

std::unordered_set<std::string> Validator::removeSlideMandatoryOperands = {
        "-slide"
    };

std::unordered_set<std::string> Validator::changeMandatoryOperands = {
        "-id"
    };

std::unordered_set<std::string> Validator::saveMandatoryOperands = {
        "-path", "-filename"
    };

std::unordered_set<std::string> Validator::loadMandatoryOperands = {
        "-path"
    };




bool Validator::validateCommand(const std::shared_ptr<Command>& commandToBeChecked) { 
    auto commandName = commandToBeChecked->getName();
    auto commandOperands = commandToBeChecked->getOperands();

// [TK] very bad style, commands should not be duplicated here, all needed info should be taken from single place i.e. Validator::validOperands, dynamically, whithout such hardcodes 
    if (commandName == "add") {
        return checkOperandQuantity(commandOperands, addValidOperands) && (checkMandatoryOperands(commandOperands,  addShapeMandatoryOperands) || checkMandatoryOperands(commandOperands, addSlideMandatoryOperands));

    } else if (commandName == "remove") {
        return checkOperandQuantity(commandOperands, removeValidOperands) && (checkMandatoryOperands(commandOperands, removeIDMandatoryOperands) || checkMandatoryOperands(commandOperands, removeSlideMandatoryOperands));

    } else if (commandName == "change") {
        return checkOperandQuantity(commandOperands, changeValidOperands) && checkMandatoryOperands(commandOperands, changeMandatoryOperands);

    } else if (commandName == "display") {
        return checkOperandQuantity(commandOperands, displayValidOperands) ;

    } else if (commandName == "save") {
        return checkOperandQuantity(commandOperands, saveValidOperands) && checkMandatoryOperands(commandOperands, saveMandatoryOperands);

    } else if (commandName == "load") {
        return checkOperandQuantity(commandOperands, loadValidOperands) && checkMandatoryOperands(commandOperands, loadMandatoryOperands);
    }

    return true;
}

bool Validator::checkOperandQuantity(std::unordered_map<std::string, std::vector<std::string>> commandOperands, std::unordered_map<std::string, size_t> validOperands) {
    for(const auto& [key, value] : commandOperands) {
        if (validOperands.at(key) != -1 && validOperands.at(key) != value.size()) {
            return false;
        }
    }
    return true;
}

bool Validator::checkMandatoryOperands(std::unordered_map<std::string, std::vector<std::string>> commandOperands, std::unordered_set<std::string> validOperands) {
    for(const auto& key: validOperands){
        if (commandOperands.find(key) == commandOperands.end()) {
            return false;
        }
    }
    return true;
}






bool Validator::isName(const std::string& inputToBeChecked) {
    return std::find(commands.begin(), commands.end(), inputToBeChecked) != commands.end();
}

bool Validator::isOperand(const std::string& inputToBeChecked, const std::string& commandName) {
    auto validOperandsForCommand = validOperands[commandName];
    return std::find(validOperandsForCommand.begin(), validOperandsForCommand.end(), inputToBeChecked) != validOperandsForCommand.end();
}

bool Validator::isDouble(const std::string& inputToBeChecked) {
    try {
        double number = std::stod(inputToBeChecked);
        return true;
    } catch (...) {
        return false;
    }
}

bool Validator::isHex(const std::string& inputToBeChecked) {
    return inputToBeChecked.size() == 7 && inputToBeChecked[0] == '#' && std::all_of(inputToBeChecked.begin() + 1, inputToBeChecked.end(), isxdigit);
}

bool Validator::isInteger(const std::string& inputToBeChecked) {
    return std::all_of(inputToBeChecked.begin(), inputToBeChecked.end(), isdigit);
}

bool Validator::isPath(const std::string& inputToBeChecked) { 
    std::ifstream file(inputToBeChecked);
    return file.good();
}

bool Validator::isFilename(const std::string& inputToBeChecked) {
    return std::all_of(inputToBeChecked.begin(), inputToBeChecked.end(), isalnum);
}

bool Validator::isStyle(const std::string& inputToBeChecked) {
    return std::find(styles.begin(), styles.end(), inputToBeChecked) != styles.end();
}



bool Validator::isValue(const std::string& inputToBeChecked, const std::string& operandName) {

    if (operandName == "-name") {
        return std::find(shapes.begin(), shapes.end(), inputToBeChecked) != shapes.end();

    } else if (operandName == "-id") {
        return isInteger(inputToBeChecked);

    } else if (operandName == "-pos") {
        return isDouble(inputToBeChecked);

    } else if (operandName == "-lcolor") {
        return isHex(inputToBeChecked);

    } else if (operandName == "-fcolor") {
        return isHex(inputToBeChecked);

    } else if (operandName == "-path") {
        return isPath(inputToBeChecked);

    } else if (operandName == "-w" || operandName == "-h") {
        return isDouble(inputToBeChecked);

    } else if (operandName == "-filename") {
        return isFilename(inputToBeChecked);
        
    } else if (operandName == "-slide") {
        return isInteger(inputToBeChecked);

    } else if (operandName == "-lwidth"){
        return isDouble(inputToBeChecked);

    } else if (operandName == "-lstyle"){
        return isStyle(inputToBeChecked);
    }
    else {
        return false;
    }
}


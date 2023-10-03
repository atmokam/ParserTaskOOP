#include "Validator.hpp"


// general checking
std::unordered_set<std::string> Validator::commands = {
        "add", "remove", "change", "display", "exit", "list", "save", "load"
    };

std::unordered_map<std::string, std::vector<std::string>> Validator::validOperands = {
        {"add", {"-name", "-pos", "-lcolor", "-fcolor", "-radius", "-w", "-h"}},
        {"remove", {"-id"}},
        {"change", {"-id", "-name", "-pos", "-lcolor", "-fcolor", "-radius", "-w", "-h"}},
        {"display", {"-id"}},
        {"exit", {}},
        {"list", {}},
        {"save", {"-path"}},
        {"load", {"-path"}}
    };

std::unordered_set<std::string> Validator::shapes = {
        "trapezoid", "rectangle", "line", "triangle", "ellipse"
    };




// operand quantity checking: 0 means no value, -1 means any number of values
std::unordered_map<std::string, size_t> Validator::addValidOperands = {
        {"-name", 1}, {"-lcolor", 1}, {"-fcolor", 1}, {"-radius", 1}, {"-pos", -1}, {"-w", 1}, {"-h", 1}
    };

std::unordered_map<std::string, size_t> Validator::removeValidOperands = {
        {"-id", 1}
    };

std::unordered_map<std::string, size_t> Validator::changeValidOperands = {
        {"-id", 1}, {"-name", 1}, {"-pos", -1}, {"-lcolor", 1}, {"-fcolor", 1}, {"-radius", 1}, {"-w", 1}, {"-h", 1}
    };

std::unordered_map<std::string, size_t> Validator::displayValidOperands = {
        {"-id", 0}
    };

std::unordered_map<std::string, size_t> Validator::saveValidOperands = {
        {"-path", 1}
    };

std::unordered_map<std::string, size_t> Validator::loadValidOperands = {
        {"-path", 1}
    };



// mandatory operand checking
std::unordered_set<std::string> Validator::addMandatoryOperands = {
        "-name", "-pos", "-w", "-h"
    };

std::unordered_set<std::string> Validator::removeMandatoryOperands = {
        "-id"
    };

std::unordered_set<std::string> Validator::changeMandatoryOperands = {
        "-id"
    };

std::unordered_set<std::string> Validator::saveMandatoryOperands = {
        "-path"
    };

std::unordered_set<std::string> Validator::loadMandatoryOperands = {
        "-path"
    };




bool Validator::validateCommand(std::shared_ptr<Command> commandToBeChecked) { 
    auto commandName = commandToBeChecked->getName();
    auto commandOperands = commandToBeChecked->getOperands();

    if (commandName == "add") {
        return checkOperandQuantity(commandOperands, addValidOperands) && checkMandatoryOperands(commandOperands,  addMandatoryOperands);

    } else if (commandName == "remove") {
        return checkOperandQuantity(commandOperands, removeValidOperands) && checkMandatoryOperands(commandOperands, removeMandatoryOperands);

    } else if (commandName == "change") {
        return checkOperandQuantity(commandOperands, changeValidOperands) && checkMandatoryOperands(commandOperands, changeMandatoryOperands);

    } else if (commandName == "display") {
        return checkOperandQuantity(commandOperands, displayValidOperands);

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






bool Validator::isName(std::string inputToBeChecked) {
    return std::find(commands.begin(), commands.end(), inputToBeChecked) != commands.end();
}

bool Validator::isOperand(std::string inputToBeChecked, std::string commandName) {
    auto validOperandsForCommand = validOperands[commandName];
    return std::find(validOperandsForCommand.begin(), validOperandsForCommand.end(), inputToBeChecked) != validOperandsForCommand.end();
}

bool Validator::isID(std::string inputToBeChecked) {
    return inputToBeChecked.size() == 8 && std::all_of(inputToBeChecked.begin(), inputToBeChecked.end(), isdigit);
}

bool Validator::isPosition(std::string inputToBeChecked) {
    try {
        double number = std::stod(inputToBeChecked);
        return true;
    } catch (...) {
        return false;
    }
}

bool Validator::isHex(std::string inputToBeChecked) {
    return inputToBeChecked.size() == 7 && inputToBeChecked[0] == '#' && std::all_of(inputToBeChecked.begin() + 1, inputToBeChecked.end(), isxdigit);
}

bool Validator::isRadius(std::string inputToBeChecked) {
    return std::all_of(inputToBeChecked.begin(), inputToBeChecked.end(), isdigit);
}

bool Validator::isPath(std::string inputToBeChecked) { 
    std::ifstream file(inputToBeChecked);
    return file.good();
}



bool Validator::isValue(std::string inputToBeChecked, std::string operandName) {

    if (operandName == "-name") {
        return std::find(shapes.begin(), shapes.end(), inputToBeChecked) != shapes.end();

    } else if (operandName == "-id") {
        return isID(inputToBeChecked);

    } else if (operandName == "-pos") {
        return isPosition(inputToBeChecked);

    } else if (operandName == "-lcolor") {
        return isHex(inputToBeChecked);

    } else if (operandName == "-fcolor") {
        return isHex(inputToBeChecked);

    } else if (operandName == "-radius") {
        return isRadius(inputToBeChecked);

    } else if (operandName == "-path") {
        return isPath(inputToBeChecked);

    } else if (operandName == "-w" || operandName == "-h") {
        return isPosition(inputToBeChecked);

    } else {
        return false;
    }
}


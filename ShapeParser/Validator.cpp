#include "Validator.hpp"




std::unordered_set<std::string> Validator::commands = {
        "add", "remove", "change", "display", "exit", "list", "save", "load"
    };

std::unordered_map<std::string, std::vector<std::string>> Validator::validOperands = {
        {"add", {"-name", "-pos", "-lcolor", "-fcolor", "-radius"}},
        {"remove", {"-id"}},
        {"change", {"-id", "-name", "-pos", "-lcolor", "-fcolor", "-radius"}},
        {"display", {"-id"}},
        {"exit", {}},
        {"list", {}},
        {"save", {"-path"}},
        {"load", {}}
    };

std::unordered_set<std::string> Validator::shapes = {
        "trapezoid", "rectangle", "line", "triangle", "ellipse"
    };




bool Validator::isName(std::string inputToBeChecked) {
    return std::find(commands.begin(), commands.end(), inputToBeChecked) != commands.end();
}

bool Validator::isOperand(std::string inputToBeChecked, std::string commandName) {
    auto validOperandsForCommand = validOperands[commandName];
    return std::find(validOperandsForCommand.begin(), validOperandsForCommand.end(), inputToBeChecked) != validOperandsForCommand.end();
}

bool Validator::validateCommand(std::unique_ptr<Command> commandToBeChecked) { ///////
    
    return true;
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

    } else {
        return false;
    }
}


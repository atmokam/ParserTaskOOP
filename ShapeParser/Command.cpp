#include "Command.hpp"


void AddCommand::execute() {
    std::cout << "AddCommand executed" << std::endl;
}

void RemoveCommand::execute() {
    std::cout << "RemoveCommand executed" << std::endl;
}

void DisplayCommand::execute() {
    std::cout << "DisplayCommand executed" << std::endl;
}

void ChangeCommand::execute() {
    std::cout << "ChangeCommand executed" << std::endl;
}

void SaveCommand::execute() {
    std::cout << "SaveCommand executed" << std::endl;
}

void LoadCommand::execute() {
    std::cout << "LoadCommand executed" << std::endl;
}

void ListCommand::execute() {
    std::cout << "ListCommand executed" << std::endl;
}

void ExitCommand::execute() {
    std::cout << "ExitCommand executed" << std::endl;
}

void Command::addOperandToOperands(std::string operand) {
    operands[operand]; // in case of no value
}

void Command::addValueToOperands(std::string value, std::string operand) {
    operands[operand].push_back(value);
}


std::string Command::getName() const {
    return name;
}

void Command::setName(std::string name) {
    this->name = name;
}


#include "Command.hpp"


void AddCommand::execute() {
    std::cout << "AddCommand executed"<< std::endl;
    std::shared_ptr<Item> item = createItem();
    std::cout << "Item created" << std::endl;
    //std:: cout << "Item wh: " << item->getBoundingRect().height << item->getBoundingRect().width << std::endl;


}

void RemoveCommand::execute() {
    std::cout << "RemoveCommand executed" << std::endl;
}

void DisplayCommand::execute() {
    std::cout << "DisplayCommand executed" << std::endl;
}

void ChangeCommand::execute() {
    std::cout << "ChangeCommand executed"<< std::endl;
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

std::shared_ptr<Item> AddCommand::createItem() {
    // return std::make_shared<Item>(
        if(Converter::convertToType(operands["-name"]) == Type::Rectangle){
            std::cout << "Circle created" << std::endl;
        }
        std::cout << Converter::convertToPosition(operands["-pos"]).getCoordinates()[0] << std::endl;
        std::cout << Converter::convertToBoundingRect(operands["-w"][0], operands["-h"][0]).height << std::endl;
        std::cout << Converter::convertToColor(operands["-lcolor"][0], operands["-fcolor"][0]).hexFillColor;
}


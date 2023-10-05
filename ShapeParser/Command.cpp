#include "Command.hpp"


void AddCommand::execute(std::shared_ptr<Slide> slide) {
    std::cout << "AddCommand executed"<< std::endl;
    std::shared_ptr<Item> item = createItem();
    slide->addItem(item);
}

void RemoveCommand::execute(std::shared_ptr<Slide> slide) {
    std::cout << "RemoveCommand executed" << std::endl;
    slide->removeItem(getItemID());

}

void DisplayCommand::execute(std::shared_ptr<Slide> slide) {
    std::cout << "DisplayCommand executed" << std::endl;
   // add conversion to string
}

void ChangeCommand::execute(std::shared_ptr<Slide> slide) {
    std::cout << "ChangeCommand executed"<< std::endl;
}

void SaveCommand::execute(std::shared_ptr<Slide> slide) {
    std::cout << "SaveCommand executed" << std::endl;
}

void LoadCommand::execute(std::shared_ptr<Slide> slide) {
    std::cout << "LoadCommand executed" << std::endl;
}

void ListCommand::execute(std::shared_ptr<Slide> slide) {
    std::cout << "ListCommand executed" << std::endl;
}

void ExitCommand::execute(std::shared_ptr<Slide> slide) {
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
        Type type = Type{Converter::convertToType(operands["-name"])};
        Position pos = Position{Converter::convertToPosition(operands["-pos"]).getCoordinates()};
        BoundingRect bounds = BoundingRect{Converter::convertToBoundingRect(operands["-w"][0], operands["-h"][0])};
        Color color;
        if(operands.find("-lcolor") != operands.end() && operands.find("-fcolor") != operands.end()){
            color = Color{Converter::convertToColor(operands["-lcolor"][0], operands["-fcolor"][0])};
        } // change so it can take one of these at a time as well
        return std::make_shared<Item>(type, pos, bounds, color);

}

int RemoveCommand::getItemID() {
    return std::stoi(operands["-id"][0]);
}


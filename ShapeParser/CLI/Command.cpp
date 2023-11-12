#include "Command.hpp"


void AddCommand::execute(std::shared_ptr<Director>& director) {

    director->setOperands(operands);
    director->addActionToHistory(director->executeAction("add"));

}

void RemoveCommand::execute(std::shared_ptr<Director>& director) {
    director->setOperands(operands);
    director->addActionToHistory(director->executeAction("remove"));

}

void DisplayCommand::execute(std::shared_ptr<Director>& director) {
    director->setOperands(operands);
    director->executeAction("display"); // should this be added to history?
}

void ChangeCommand::execute(std::shared_ptr<Director>& director) {
    director->setOperands(operands);
    director->addActionToHistory(director->executeAction("change"));
}


void SaveCommand::execute(std::shared_ptr<Director>& director) {
        
    director->setOperands(operands);
    director->executeAction("save");

}

void LoadCommand::execute(std::shared_ptr<Director>& director) { 
    
    director->setOperands(operands);
    director->executeAction("load");

}


void ListCommand::execute(std::shared_ptr<Director>& director) {
    
    director->setOperands(operands);
    director->executeAction("list");
    
}

void NextCommand::execute(std::shared_ptr<Director>& director) {
    
    director->setOperands(operands);
    director->addActionToHistory(director->executeAction("next"));

}

void PrevCommand::execute(std::shared_ptr<Director>& director) {
    
    director->setOperands(operands);
    director->addActionToHistory(director->executeAction("prev"));
}




void Command::addOperandToOperands(std::string operand) {
    operands[operand];                           // in case of no value
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

std::unordered_map<std::string, std::vector<std::string>> Command::getOperands() const {
    return operands;
}
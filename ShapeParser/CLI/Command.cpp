#include "Command.hpp"


void AddCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {

    AddAction action(operands);
    action.execute(document, view);
}

void RemoveCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
    RemoveAction action(operands);
    action.execute(document, view);

}

void DisplayCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
    DisplayAction action(operands);
    action.execute(document, view);
}

void ChangeCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
    ChangeAction action(operands);
    action.execute(document, view);
}


void SaveCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
        
    SaveAction action(operands);
    action.execute(document, view); // these are for the sake of consistency

}

void LoadCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) { 
    
    LoadAction action(operands);
    action.execute(document, view);

}



void ListCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
    
    ListAction action(operands);
    action.execute(document, view);
    
}

void NextCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
    
    NextAction action(operands);
    action.execute(document, view);

}

void PrevCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
    
    PrevAction action(operands);
    action.execute(document, view);
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



#include "Command.hpp"


void AddCommand::execute(std::shared_ptr<Director>& director) {

   if(operands.find("-name") != operands.end()){
        std::shared_ptr<Item> item = createItem(director->getCurrentSlideNumber());
        std::shared_ptr<IAction> action = director->createAction(ActionType::AddItem, item);
        director->addActionToHistory(action->execute(director->getDocument())); // command has to handle the history adding part
        std::cout << "Added new item" << std::endl;
    }
    else if(operands.find("-slide") != operands.end()){
        std::shared_ptr<IAction> action = director->createAction(ActionType::AddSlide, std::make_shared<Slide>());
        director->addActionToHistory(action->execute(director->getDocument()));
        std::cout << "Added new slide" << std::endl;
    }

}

std::shared_ptr<Item> AddCommand::createItem(const std::shared_ptr<Slide>& slide) {


    Type type = Type{Converter::convertToType(operands["-name"])};

    Position pos = Position{Converter::convertToPosition(operands["-pos"])};

    BoundingRect bounds = BoundingRect{Converter::convertToBoundingRect(operands["-w"][0], operands["-h"][0])};
    
    Color color; LineDescriptor lineDescriptor;
    if(operands.find("-lcolor") != operands.end()){
        color.hexLineColor = Converter::convertToColor(operands["-lcolor"][0]);
    }
    if (operands.find("-fcolor") != operands.end()){
        color.hexFillColor = Converter::convertToColor(operands["-fcolor"][0]);
    }
    if (operands.find("-lwidth") != operands.end()){
        lineDescriptor.width = std::stod(operands["-lwidth"][0]);
    }
    if (operands.find("-lstyle") != operands.end()){
        lineDescriptor.type = Converter::convertToLineType(operands["-lstyle"][0]);
    }

    auto item = std::make_shared<Item>(type, pos, bounds, color, slide->generateID(), lineDescriptor);

    return item;
}

void RemoveCommand::execute(std::shared_ptr<Director>& director) {
    if(operands.find("-id") != operands.end()){
        std::shared_ptr<Item> undoItem = director->getCurrentSlide()->getItem(std::stoi(operands["-id"][0]));
        std::shared_ptr<IAction> action = director->createAction(ActionType::RemoveItem, undoItem);
        director->addActionToHistory(action->execute(director->getDocument()));
    }
    else if(operands.find("-slide") != operands.end()){
        if(director->getDocument()->size() == 1){
            std::cout << "Cannot remove slide, only 1 left" << std::endl;
            
        } else {
            std::shared_ptr<IAction> action = director->createAction(ActionType::RemoveSlide, director->getCurrentSlide());
            director->addActionToHistory(action->execute(director->getDocument())); // director has the slide it needs to remove
        }
        
    }

}

void DisplayCommand::execute(std::shared_ptr<Director>& director) {
    if(operands.find("-id") != operands.end()){
        displayItem(getCurrentSlide(document, currentSlideIndex)->getItem(std::stoi(operands["-id"][0])));
    }//// --------------------------------------------------------- //////
    else{
        std::cout << "---------Current slide (" << currentSlideIndex << ")---------" << std::endl; 
        std::shared_ptr<Slide> slide = getCurrentSlide(document, currentSlideIndex);
        for(auto item : *slide){
            displayItem(item.second);
        }
    }
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
#include "Command.hpp"


void AddCommand::execute(std::shared_ptr<Slide> slide) {
    std::shared_ptr<Item> item = createItem();
    slide->addItem(item);
}

void RemoveCommand::execute(std::shared_ptr<Slide> slide) {
    slide->removeItem(getItemID());

}

void DisplayCommand::execute(std::shared_ptr<Slide> slide) {
    if(operands.find("-id") != operands.end()){
        std::shared_ptr<Item> item = slide->getItem(std::stoi(operands["-id"][0]));
        displayItem(item);
    }
    else{
        std::unordered_map<int, std::shared_ptr<Item>> items = slide->getItems();
        for(auto item : items){
            displayItem(item.second);
        }
    }
}

void ChangeCommand::execute(std::shared_ptr<Slide> slide) {
    if(operands.find("-pos") != operands.end()){
        slide->getItem(std::stoi(operands["-id"][0]))->setPosition(Converter::convertToPosition(operands["-pos"]));
    }
    if(operands.find("-name") != operands.end()){
        slide->getItem(std::stoi(operands["-id"][0]))->setType(Type{Converter::convertToType(operands["-name"])});
    }
    if(operands.find("-w") != operands.end() && operands.find("-h") != operands.end()){
        slide->getItem(std::stoi(operands["-id"][0]))->setBoundingRect(BoundingRect{Converter::convertToBoundingRect(operands["-w"][0], operands["-h"][0])});
    }
    if(operands.find("-lcolor") != operands.end()){
        slide->getItem(std::stoi(operands["-id"][0]))->setLineColor(Converter::convertToColor(operands["-lcolor"][0]));
    }
    if(operands.find("-fcolor") != operands.end()){
        slide->getItem(std::stoi(operands["-id"][0]))->setFillColor(Converter::convertToColor(operands["-fcolor"][0]));
    }
}

void SaveCommand::execute(std::shared_ptr<Slide> slide) {
    std::ofstream file;
    if(operands.find("-path") != operands.end()){
        file.open(operands["-path"][0] + "output.ppx", std::ios_base::app);

    }
    
    if(!file.is_open()){
        throw std::invalid_argument("Invalid path");
    }

    std::unordered_map<int, std::shared_ptr<Item>> items = slide->getItems();
    for(auto& [id, item] : items){                          // add a function to separate this part
        file << "ID: " << item->getID() << std::endl;
        file << "Type: " << ShapeType{item->getType()} << std::endl;
        file << "Position: " << item->getPosition() << std::endl;
        file << "Bounding Rectangle: " << item->getBoundingRect() << std::endl;
        file << "Color: " << item->getColor() << std::endl;
        file << std::endl;
    }
}

void LoadCommand::execute(std::shared_ptr<Slide> slide) { // should this start everything over?
    std::cout << "LoadCommand executed" << std::endl;
}

void ListCommand::execute(std::shared_ptr<Slide> slide) {
    
    std::unordered_map<int, std::shared_ptr<Item>> items = slide->getItems();
    for(auto item : items) {
        displayItem(item.second);
    }
    
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




std::shared_ptr<Item> AddCommand::createItem() {

    Type type = Type{Converter::convertToType(operands["-name"])};

    Position pos = Position{Converter::convertToPosition(operands["-pos"]).getCoordinates()};

    BoundingRect bounds = BoundingRect{Converter::convertToBoundingRect(operands["-w"][0], operands["-h"][0])};
    
    Color color;
    if(operands.find("-lcolor") != operands.end()){
        color.hexLineColor = Converter::convertToColor(operands["-lcolor"][0]);
    }
    if (operands.find("-fcolor") != operands.end()){
        color.hexFillColor = Converter::convertToColor(operands["-fcolor"][0]);
    }
    return std::make_shared<Item>(type, pos, bounds, color);

}

int RemoveCommand::getItemID() {
    return std::stoi(operands["-id"][0]);
}
 
void DisplayCommand::displayItem(std::shared_ptr<Item> item) {
    std::cout << "ID: " << item->getID() << std::endl;
    std::cout << "Type: " << ShapeType{item->getType()} << std::endl;
    std::cout << "Position: " << item->getPosition() << std::endl;
    std::cout << "Bounding Rectangle: " << item->getBoundingRect() << std::endl;
    std::cout << "Color: " << item->getColor() << std::endl;
    std::cout << std::endl;
}


void ListCommand::displayItem(std::shared_ptr<Item> item) {
    std::cout << "ID: " << item->getID() << std::endl;
    std::cout << "Type: " << ShapeType{item->getType()} << std::endl;
    std::cout << "Position: " << item->getPosition() << std::endl;
    std::cout << "Bounding Rectangle: " << item->getBoundingRect() << std::endl;
    std::cout << "Color: " << item->getColor() << std::endl;
    std::cout << std::endl;
}



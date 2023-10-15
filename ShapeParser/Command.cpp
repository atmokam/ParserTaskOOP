#include "Command.hpp"


void AddCommand::execute(std::shared_ptr<Document> document, std::shared_ptr<View> view) {
    std::shared_ptr<Item> item = createItem();
    getSlide(document, view)->addItem(item);
} // this is because (imo) the slide shouldn't know its number, but the view should

void RemoveCommand::execute(std::shared_ptr<Document> document, std::shared_ptr<View> view) {
    getSlide(document, view)->removeItem(getItemID());

}

void DisplayCommand::execute(std::shared_ptr<Document> document, std::shared_ptr<View> view) {
    if(operands.find("-id") != operands.end()){
        std::shared_ptr<Item> item = getSlide(document, view)->getItem(std::stoi(operands["-id"][0]));
        displayItem(item);
    }
    else{
        std::unordered_map<int, std::shared_ptr<Item>> items = getSlide(document, view)->getItems();
        for(auto item : items){
            displayItem(item.second);
        }
    }
}

void ChangeCommand::execute(std::shared_ptr<Document> document, std::shared_ptr<View> view) {
    if(operands.find("-pos") != operands.end()){
        getSlide(document, view)->getItem(std::stoi(operands["-id"][0]))->setPosition(Converter::convertToPosition(operands["-pos"]));
    }
    if(operands.find("-name") != operands.end()){
        getSlide(document, view)->getItem(std::stoi(operands["-id"][0]))->setType(Type{Converter::convertToType(operands["-name"])});
    }
    if(operands.find("-w") != operands.end() && operands.find("-h") != operands.end()){
        getSlide(document, view)->getItem(std::stoi(operands["-id"][0]))->setBoundingRect(BoundingRect{Converter::convertToBoundingRect(operands["-w"][0], operands["-h"][0])});
    }
    if(operands.find("-lcolor") != operands.end()){
        getSlide(document, view)->getItem(std::stoi(operands["-id"][0]))->setLineColor(Converter::convertToColor(operands["-lcolor"][0]));
    }
    if(operands.find("-fcolor") != operands.end()){
        getSlide(document, view)->getItem(std::stoi(operands["-id"][0]))->setFillColor(Converter::convertToColor(operands["-fcolor"][0]));
    }
}

void SaveCommand::execute(std::shared_ptr<Document> document, std::shared_ptr<View> view) {
    std::ofstream file;
    
    auto path = operands["-path"][0];
    auto filename = operands["-filename"][0];
    file.open(path + filename + ".ppx");

    if(!file.is_open()){
        throw std::invalid_argument("Invalid path or filename");
    }

    file << "slide: " << view->currentSlideNumber << std::endl;

    std::unordered_map<int, std::shared_ptr<Item>> items = getSlide(document, view)->getItems();
    // save to file 
    saveToFile(file, document->getSlide(view->currentSlideNumber)->getItems());

}

void SaveCommand::saveToFile(std::ofstream& file, const std::unordered_map<int, std::shared_ptr<Item>>& items) {
    for(auto item : items) {
        file << item.second->getID() << std::endl;
        file << ShapeType{item.second->getType()} << std::endl;
        file << item.second->getPosition() << std::endl;
        file << item.second->getBoundingRect() << std::endl;
        file << item.second->getColor() << std::endl;
        file << std::endl;
    }
}

void LoadCommand::execute(std::shared_ptr<Document> document, std::shared_ptr<View> view) { 
    std::cout << "LoadCommand executed" << std::endl;
}

void ListCommand::execute(std::shared_ptr<Document> document, std::shared_ptr<View> view) {
    
    std::unordered_map<int, std::shared_ptr<Item>> items = getSlide(document, view)->getItems();
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
 


void displayItem(std::shared_ptr<Item> item) {
    std::cout << "ID: " << item->getID() << std::endl;
    std::cout << "Type: " << ShapeType{item->getType()} << std::endl;
    std::cout << "Position: " << item->getPosition() << std::endl;
    std::cout << "Bounding Rectangle: " << item->getBoundingRect() << std::endl;
    std::cout << "Color: " << item->getColor() << std::endl;
    std::cout << std::endl;
}


std::shared_ptr<Slide> Command::getSlide(std::shared_ptr<Document> document, std::shared_ptr<View> view) const {
    return document->getSlide(view->currentSlideNumber); 
}


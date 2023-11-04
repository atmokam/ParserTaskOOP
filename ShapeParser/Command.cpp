#include "Command.hpp"


void AddCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {

    if(operands.find("-name") != operands.end()){
        std::shared_ptr<Item> item = createItem(getCurrentSlide(document, view));
        getCurrentSlide(document, view)->addItem(item);
    }
    else if(operands.find("-slide") != operands.end()){
        std::cout << "- - - - - - - - - - Added new slide - - - - - - - - - -" << std::endl;
        document->addSlide(std::make_shared<Slide>());
        //view->currentSlideNumber++; // change
    }
}

void RemoveCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
    if(operands.find("-id") != operands.end()){
        getCurrentSlide(document, view)->removeItem(getItemID());
    }
    else if(operands.find("-slide") != operands.end()){
        if(view->currentSlideNumber == 0){
            std::cout << "Cannot remove first slide" << std::endl;
            return;
        }
        document->removeSlide(view->currentSlideNumber);
        view->currentSlideNumber--;
    }

}

void DisplayCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
    if(operands.find("-id") != operands.end()){
        displayItem(getCurrentSlide(document, view)->getItem(std::stoi(operands["-id"][0])));
    }
    else{
        std::cout << "---------Current slide (" << view->currentSlideNumber << ")---------" << std::endl; 
        std::shared_ptr<Slide> slide = getCurrentSlide(document, view);
        for(auto item : *slide){
            displayItem(item.second);
        }
    }
}

void ChangeCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
    if(operands.find("-pos") != operands.end()){
        getCurrentSlide(document, view)->getItem(std::stoi(operands["-id"][0]))->setPosition(Converter::convertToPosition(operands["-pos"]));
    }
    if(operands.find("-name") != operands.end()){
        getCurrentSlide(document, view)->getItem(std::stoi(operands["-id"][0]))->setType(Type{Converter::convertToType(operands["-name"])});
    }
    if(operands.find("-w") != operands.end() && operands.find("-h") != operands.end()){
        getCurrentSlide(document, view)->getItem(std::stoi(operands["-id"][0]))->setBoundingRect(BoundingRect{Converter::convertToBoundingRect(operands["-w"][0], operands["-h"][0])});
    }
    if(operands.find("-lcolor") != operands.end()){
        getCurrentSlide(document, view)->getItem(std::stoi(operands["-id"][0]))->setLineColor(Converter::convertToColor(operands["-lcolor"][0]));
    }
    if(operands.find("-fcolor") != operands.end()){
        getCurrentSlide(document, view)->getItem(std::stoi(operands["-id"][0]))->setFillColor(Converter::convertToColor(operands["-fcolor"][0]));
    }
}


void SaveCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
    SaveLoadSerializer::save(document, operands["-path"][0] + operands["-filename"][0]);

}

void LoadCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) { 
    std::ifstream file;
    auto path = operands["-path"][0];

    file.open(path);
    if(!file.is_open()){
        throw std::invalid_argument("Invalid path or filename");
    }

    document = SaveLoadSerializer::load(path);

    view->currentSlideNumber = 0;
    view->currentSlide = getCurrentSlide(document, view);

}



void ListCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
    
    std::cout << "-------------------------------List of slides---------------------------------" << std::endl;

    int i = 0;
    for(auto slide : *document){
        std::cout << "---------Slide number " << i++ << "---------" << std::endl;
        for(auto item : *slide) {
            displayItem(item.second);
        }
    }
    
}

void NextCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
    if(view->currentSlideNumber < std::distance(document->cbegin(), document->cend()) - 1){
        view->currentSlideNumber++;
        view->currentSlide = getCurrentSlide(document, view);
    }
    else{
        std::cout << "No next slide" << std::endl;
    }
}

void PrevCommand::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
    if(view->currentSlideNumber > 0){
        view->currentSlideNumber--;
        view->currentSlide = getCurrentSlide(document, view);
    }
    else{
        std::cout << "No previous slide" << std::endl;
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




std::shared_ptr<Item> AddCommand::createItem(std::shared_ptr<Slide> slide) {


    Type type = Type{Converter::convertToType(operands["-name"])};

    Position pos = Position{Converter::convertToPosition(operands["-pos"])};

    BoundingRect bounds = BoundingRect{Converter::convertToBoundingRect(operands["-w"][0], operands["-h"][0])};
    
    Color color;
    if(operands.find("-lcolor") != operands.end()){
        color.hexLineColor = Converter::convertToColor(operands["-lcolor"][0]);
    }
    if (operands.find("-fcolor") != operands.end()){
        color.hexFillColor = Converter::convertToColor(operands["-fcolor"][0]);
    }
    auto item = std::make_shared<Item>(type, pos, bounds, color, slide->generateID());

    return item;

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


std::shared_ptr<Slide> Command::getCurrentSlide(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) const {
    return document->getSlide(view->currentSlideNumber); 
}



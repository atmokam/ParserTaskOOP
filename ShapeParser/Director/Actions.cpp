#include "Director/Actions.hpp"

Action::Action(std::unordered_map<std::string, std::vector<std::string>>& operands) : operands(operands) {}

AddAction::AddAction(std::unordered_map<std::string, std::vector<std::string>>& operands) : Action(operands) {}

void AddAction::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {

    if(operands.find("-name") != operands.end()){
        std::shared_ptr<Item> item = createItem(getCurrentSlide(document, view));
        getCurrentSlide(document, view)->addItem(item);
    }
    else if(operands.find("-slide") != operands.end()){
        std::cout << "- - - - - - - - - - Added new slide - - - - - - - - - -" << std::endl;
        document->addSlide(std::make_shared<Slide>());
    }
    
}

std::shared_ptr<Slide> Action::getCurrentSlide(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) const {
    return document->getSlide(view->currentSlideNumber);
}

std::shared_ptr<Item> AddAction::createItem(const std::shared_ptr<Slide>& slide) {


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

RemoveAction::RemoveAction(std::unordered_map<std::string, std::vector<std::string>>& operands) : Action(operands) {}

void RemoveAction::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view){
  if(operands.find("-id") != operands.end()){
        getCurrentSlide(document, view)->removeItem(std::stoi(operands["-id"][0]));
    }
    else if(operands.find("-slide") != operands.end()){
        if(std::distance(document->cbegin(), document->cend()) == 1){
            std::cout << "Cannot remove slide, only 1 left" << std::endl;
            return;
        }
        document->removeSlide(view->currentSlideNumber);
        view->currentSlideNumber--;
    }
}

DisplayAction::DisplayAction(std::unordered_map<std::string, std::vector<std::string>>& operands) : Action(operands) {}

void DisplayAction::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
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

void DisplayAction::displayItem(const std::shared_ptr<Item>& item) {
    std::cout << "ID: " << item->getID() << std::endl;
    std::cout << "Type: " << ShapeType{item->getType()} << std::endl;
    std::cout << "Position: " << item->getPosition() << std::endl;
    std::cout << "Bounding Rectangle: " << item->getBoundingRect() << std::endl;
    std::cout << "Color: " << item->getColor() << std::endl;
    std::cout << "Line Descriptor: " << item->getLineDescriptor() << std::endl;
    std::cout << std::endl;
}


ChangeAction::ChangeAction(std::unordered_map<std::string, std::vector<std::string>>& operands) : Action(operands) {}

void ChangeAction::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
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
    if(operands.find("-lwidth") != operands.end()){
        getCurrentSlide(document, view)->getItem(std::stoi(operands["-id"][0]))->setLineDescriptorWidth(std::stod(operands["-lwidth"][0]));
    }
    if(operands.find("-lstyle") != operands.end()){
        getCurrentSlide(document, view)->getItem(std::stoi(operands["-id"][0]))->setLineDescriptorStyle(Converter::convertToLineType(operands["-lstyle"][0]));
    }
}

ListAction::ListAction(std::unordered_map<std::string, std::vector<std::string>>& operands) : Action(operands) {}

void ListAction::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
    
    std::cout << "-------------------------------List of slides---------------------------------" << std::endl;

    int i = 0;
    for(auto slide : *document){
        std::cout << "---------Slide number " << i++ << "---------" << std::endl;
        for(auto item : *slide) {
            displayItem(item.second);
        }
    }
    
}

void ListAction::displayItem(const std::shared_ptr<Item>& item) {
    std::cout << "ID: " << item->getID() << std::endl;
    std::cout << "Type: " << ShapeType{item->getType()} << std::endl;
    std::cout << "Position: " << item->getPosition() << std::endl;
    std::cout << "Bounding Rectangle: " << item->getBoundingRect() << std::endl;
    std::cout << "Color: " << item->getColor() << std::endl;
    std::cout << "Line Descriptor: " << item->getLineDescriptor() << std::endl;
    std::cout << std::endl;
}

NextAction::NextAction(std::unordered_map<std::string, std::vector<std::string>>& operands) : Action(operands) {}

void NextAction::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
    if(view->currentSlideNumber < std::distance(document->cbegin(), document->cend()) - 1){
        view->currentSlideNumber++;
        view->currentSlide = getCurrentSlide(document, view);
    }
    else{
        std::cout << "No next slide" << std::endl;
    }
}

PrevAction::PrevAction(std::unordered_map<std::string, std::vector<std::string>>& operands) : Action(operands) {}

void PrevAction::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
    if(view->currentSlideNumber > 0){
        view->currentSlideNumber--;
        view->currentSlide = getCurrentSlide(document, view);
    }
    else{
        std::cout << "No previous slide" << std::endl;
    }
}

SaveAction::SaveAction(std::unordered_map<std::string, std::vector<std::string>>& operands) : Action(operands) {}

void SaveAction::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) {
    SaveLoadSerializer::save(document, operands["-path"][0] + operands["-filename"][0]);

}

LoadAction::LoadAction(std::unordered_map<std::string, std::vector<std::string>>& operands) : Action(operands) {}

void LoadAction::execute(std::shared_ptr<Document>& document, const std::shared_ptr<View>& view) { 
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


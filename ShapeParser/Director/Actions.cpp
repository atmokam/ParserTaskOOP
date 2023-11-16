#include "Director/Actions.hpp"


std::unordered_map<std::string, std::vector<std::string>> Action::createOperands(std::string actionType, std::vector<std::string> operands){
    return {{actionType, operands}};
}

std::shared_ptr<Slide> Action::getCurrentSlide(std::shared_ptr<Document>& document, size_t& currentSlideIndex) const {
    return document->getSlide(currentSlideIndex);
}





AddAction::AddAction(std::unordered_map<std::string, std::vector<std::string>> operands) : operands(operands) {}


std::shared_ptr<Action> AddAction::execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) {
    
    if(operands.find("-name") != operands.end()){
        std::shared_ptr<Item> item = createItem(getCurrentSlide(document, currentSlideIndex));
        getCurrentSlide(document, currentSlideIndex)->addItem(item);
        return std::make_shared<RemoveAction>(RemoveAction(createOperands("-id", {std::to_string(item->getID())})));
    }
    else if(operands.find("-slide") != operands.end()){
        std::cout << "- - - - - - - - - - Added new slide - - - - - - - - - -" << std::endl;
        document->addSlide(std::make_shared<Slide>());
        return std::make_shared<RemoveAction>(RemoveAction(createOperands("-slide", {std::to_string(std::distance(document->cbegin(), document->cend()) - 1)})));
    }
    return nullptr;
    
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

RemoveAction::RemoveAction(std::unordered_map<std::string, std::vector<std::string>> operands) : operands(operands) {}

std::shared_ptr<Action> RemoveAction::execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex){
  if(operands.find("-id") != operands.end()){
        std::shared_ptr<Item> undoItem = getCurrentSlide(document, currentSlideIndex)->getItem(std::stoi(operands["-id"][0]));
        getCurrentSlide(document, currentSlideIndex)->removeItem(std::stoi(operands["-id"][0]));
        return std::make_shared<AddAction>(AddAction()); 
    }
    else if(operands.find("-slide") != operands.end()){
        if(std::distance(document->cbegin(), document->cend()) == 1){
            std::cout << "Cannot remove slide, only 1 left" << std::endl;
            
        } else {
            document->removeSlide(currentSlideIndex);
            --currentSlideIndex;
        }
        
    }
    return nullptr;
}

DisplayAction::DisplayAction(const std::unordered_map<std::string, std::vector<std::string>>& operands) : operands(operands) {}

std::shared_ptr<Action> DisplayAction::execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) {
    if(operands.find("-id") != operands.end()){
        displayItem(getCurrentSlide(document, currentSlideIndex)->getItem(std::stoi(operands["-id"][0])));
    }
    else{
        std::cout << "---------Current slide (" << currentSlideIndex << ")---------" << std::endl; 
        std::shared_ptr<Slide> slide = getCurrentSlide(document, currentSlideIndex);
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


ChangeAction::ChangeAction(const std::unordered_map<std::string, std::vector<std::string>>& operands) : operands(operands) {}

std::shared_ptr<Action> ChangeAction::execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) {
    if(operands.find("-pos") != operands.end()){
        getCurrentSlide(document, currentSlideIndex)->getItem(std::stoi(operands["-id"][0]))->setPosition(Converter::convertToPosition(operands["-pos"]));
    }
    if(operands.find("-name") != operands.end()){
        getCurrentSlide(document, currentSlideIndex)->getItem(std::stoi(operands["-id"][0]))->setType(Type{Converter::convertToType(operands["-name"])});
    }
    if(operands.find("-w") != operands.end() && operands.find("-h") != operands.end()){
        getCurrentSlide(document, currentSlideIndex)->getItem(std::stoi(operands["-id"][0]))->setBoundingRect(BoundingRect{Converter::convertToBoundingRect(operands["-w"][0], operands["-h"][0])});
    }
    if(operands.find("-lcolor") != operands.end()){
        getCurrentSlide(document, currentSlideIndex)->getItem(std::stoi(operands["-id"][0]))->setLineColor(Converter::convertToColor(operands["-lcolor"][0]));
    }
    if(operands.find("-fcolor") != operands.end()){
        getCurrentSlide(document, currentSlideIndex)->getItem(std::stoi(operands["-id"][0]))->setFillColor(Converter::convertToColor(operands["-fcolor"][0]));
    }
    if(operands.find("-lwidth") != operands.end()){
        getCurrentSlide(document, currentSlideIndex)->getItem(std::stoi(operands["-id"][0]))->setLineDescriptorWidth(std::stod(operands["-lwidth"][0]));
    }
    if(operands.find("-lstyle") != operands.end()){
        getCurrentSlide(document, currentSlideIndex)->getItem(std::stoi(operands["-id"][0]))->setLineDescriptorStyle(Converter::convertToLineType(operands["-lstyle"][0]));
    }
}

ListAction::ListAction(const std::unordered_map<std::string, std::vector<std::string>>& operands) : operands(operands) {}

std::shared_ptr<Action> ListAction::execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) {
    
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

NextAction::NextAction(const std::unordered_map<std::string, std::vector<std::string>>& operands) : operands(operands) {}

std::shared_ptr<Action> NextAction::execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) {
    if(currentSlideIndex < std::distance(document->cbegin(), document->cend()) - 1){
        currentSlideIndex++;
    }
    else{
        std::cout << "No next slide" << std::endl;
    }
}

PrevAction::PrevAction(const std::unordered_map<std::string, std::vector<std::string>>& operands) : operands(operands) {}

std::shared_ptr<Action> PrevAction::execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) {
    if(currentSlideIndex > 0){
        currentSlideIndex--;
    }
    else{
        std::cout << "No previous slide" << std::endl;
    }
}

SaveAction::SaveAction(const std::unordered_map<std::string, std::vector<std::string>>& operands) : operands(operands) {}

std::shared_ptr<Action> SaveAction::execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) {
    SaveLoadSerializer::save(document, operands["-path"][0] + operands["-filename"][0]);

}

LoadAction::LoadAction(const std::unordered_map<std::string, std::vector<std::string>>& operands) : operands(operands) {}

std::shared_ptr<Action> LoadAction::execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) { 
    std::ifstream file;
    auto path = operands["-path"][0];

    file.open(path);
    if(!file.is_open()){
        throw std::invalid_argument("Invalid path or filename");
    }

    document = SaveLoadSerializer::load(path);

    currentSlideIndex = 0;

}


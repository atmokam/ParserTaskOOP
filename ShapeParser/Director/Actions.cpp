#include "Director/Actions.hpp"



AddItem::AddItem(const std::shared_ptr<Item>& item, size_t slideNumber) : item(item), slideNumber(slideNumber) {}

std::shared_ptr<IModifierAction> AddItem::execute(std::shared_ptr<Document>& document) {
    document->getSlide(slideNumber)->addItem(item);
    return std::make_shared<RemoveItem>(item);
    
}

AddSlide::AddSlide(const std::shared_ptr<Slide>& slide, size_t slideNumber) : slide(slide), slideNumber(slideNumber) {}

std::shared_ptr<IModifierAction> AddSlide::execute(std::shared_ptr<Document>& document) {
    document->addSlide(slide, slideNumber);
    return std::make_shared<RemoveSlide>(slide);
}

RemoveItem::RemoveItem(const std::shared_ptr<Item>& item, size_t slideNumber) : item(item), slideNumber(slideNumber) {}

std::shared_ptr<IModifierAction> RemoveItem::execute(std::shared_ptr<Document>& document) {
    document->getSlide(slideNumber)->removeItem(item->getID());
    return std::make_shared<AddItem>(item);
}

RemoveSlide::RemoveSlide(const std::shared_ptr<Slide>& slide, size_t slideNumber) : slide(slide), slideNumber(slideNumber) {}

std::shared_ptr<IModifierAction> RemoveSlide::execute(std::shared_ptr<Document>& document) {
    document->removeSlide(slide);
    return std::make_shared<AddSlide>(slide, slideNumber);
}

ChangeItem::ChangeItem(const std::shared_ptr<Item>& item) : item(item) {}   

std::shared_ptr<IModifierAction> ChangeItem::execute(std::shared_ptr<Document>& document) {
    std::shared_ptr<Item> oldItem = document->getSlide(item->getSlideNumber())->getItem(item->getID()); // item has the same id number
    document->getSlide(item->getSlideNumber())->swapItems(item->getID(), item);
    return std::make_shared<ChangeItem>(oldItem);
}




DisplayItem::DisplayItem(const std::shared_ptr<Item>& item) : item(item) {}

void DisplayItem::execute() {
    displayItem(item);
}

void DisplayItem::displayItem(const std::shared_ptr<Item>& item) {
    std::cout << "ID: " << item->getID() << std::endl;
    std::cout << "Type: " << ShapeType{item->getType()} << std::endl;
    std::cout << "Position: " << item->getPosition() << std::endl;
    std::cout << "Bounding Rectangle: " << item->getBoundingRect() << std::endl;
    std::cout << "Color: " << item->getColor() << std::endl;
    std::cout << "Line Descriptor: " << item->getLineDescriptor() << std::endl;
    std::cout << std::endl;
}

DisplaySlide::DisplaySlide(const std::shared_ptr<Slide>& slide) : slide(slide) {}

void DisplaySlide::execute() {
    displaySlide(slide);
}

void DisplaySlide::displaySlide(const std::shared_ptr<Slide>& slide) {
    std::cout << "---------Slide number " << slide->getSlideNumber() << "---------" << std::endl;
    
    for(auto item : *slide) {
        DisplayItem displayItem(item.second);
        displayItem.execute();
    }
}

List::List(const std::shared_ptr<Document>& document) : document(document) {}

void List::execute() {
    std::cout << "-------------------------------List of slides---------------------------------" << std::endl;

    int i = 0;
    for(auto slide : *document){
        std::cout << "---------Slide number " << i++ << "---------" << std::endl;
        DisplaySlide displaySlide(slide);
        displaySlide.execute();
    }
}





// ChangeAction::ChangeAction(const std::unordered_map<std::string, std::vector<std::string>>& operands) : operands(operands) {}

// std::shared_ptr<Action> ChangeAction::execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) {
//     if(operands.find("-pos") != operands.end()){
//         getCurrentSlide(document, currentSlideIndex)->getItem(std::stoi(operands["-id"][0]))->setPosition(Converter::convertToPosition(operands["-pos"]));
//     }
//     if(operands.find("-name") != operands.end()){
//         getCurrentSlide(document, currentSlideIndex)->getItem(std::stoi(operands["-id"][0]))->setType(Type{Converter::convertToType(operands["-name"])});
//     }
//     if(operands.find("-w") != operands.end() && operands.find("-h") != operands.end()){
//         getCurrentSlide(document, currentSlideIndex)->getItem(std::stoi(operands["-id"][0]))->setBoundingRect(BoundingRect{Converter::convertToBoundingRect(operands["-w"][0], operands["-h"][0])});
//     }
//     if(operands.find("-lcolor") != operands.end()){
//         getCurrentSlide(document, currentSlideIndex)->getItem(std::stoi(operands["-id"][0]))->setLineColor(Converter::convertToColor(operands["-lcolor"][0]));
//     }
//     if(operands.find("-fcolor") != operands.end()){
//         getCurrentSlide(document, currentSlideIndex)->getItem(std::stoi(operands["-id"][0]))->setFillColor(Converter::convertToColor(operands["-fcolor"][0]));
//     }
//     if(operands.find("-lwidth") != operands.end()){
//         getCurrentSlide(document, currentSlideIndex)->getItem(std::stoi(operands["-id"][0]))->setLineDescriptorWidth(std::stod(operands["-lwidth"][0]));
//     }
//     if(operands.find("-lstyle") != operands.end()){
//         getCurrentSlide(document, currentSlideIndex)->getItem(std::stoi(operands["-id"][0]))->setLineDescriptorStyle(Converter::convertToLineType(operands["-lstyle"][0]));
//     }
// }

// ListAction::ListAction(const std::unordered_map<std::string, std::vector<std::string>>& operands) : operands(operands) {}

// std::shared_ptr<Action> ListAction::execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) {
    
//     std::cout << "-------------------------------List of slides---------------------------------" << std::endl;

//     int i = 0;
//     for(auto slide : *document){
//         std::cout << "---------Slide number " << i++ << "---------" << std::endl;
//         for(auto item : *slide) {
//             displayItem(item.second);
//         }
//     }
    
// }

// void ListAction::displayItem(const std::shared_ptr<Item>& item) {
//     std::cout << "ID: " << item->getID() << std::endl;
//     std::cout << "Type: " << ShapeType{item->getType()} << std::endl;
//     std::cout << "Position: " << item->getPosition() << std::endl;
//     std::cout << "Bounding Rectangle: " << item->getBoundingRect() << std::endl;
//     std::cout << "Color: " << item->getColor() << std::endl;
//     std::cout << "Line Descriptor: " << item->getLineDescriptor() << std::endl;
//     std::cout << std::endl;
// }

// NextAction::NextAction(const std::unordered_map<std::string, std::vector<std::string>>& operands) : operands(operands) {}

// std::shared_ptr<Action> NextAction::execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) {
//     if(currentSlideIndex < std::distance(document->cbegin(), document->cend()) - 1){
//         currentSlideIndex++;
//     }
//     else{
//         std::cout << "No next slide" << std::endl;
//     }
// }

// PrevAction::PrevAction(const std::unordered_map<std::string, std::vector<std::string>>& operands) : operands(operands) {}

// std::shared_ptr<Action> PrevAction::execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) {
//     if(currentSlideIndex > 0){
//         currentSlideIndex--;
//     }
//     else{
//         std::cout << "No previous slide" << std::endl;
//     }
// }

// SaveAction::SaveAction(const std::unordered_map<std::string, std::vector<std::string>>& operands) : operands(operands) {}

// std::shared_ptr<Action> SaveAction::execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) {
//     SaveLoadSerializer::save(document, operands["-path"][0] + operands["-filename"][0]);

// }

// LoadAction::LoadAction(const std::unordered_map<std::string, std::vector<std::string>>& operands) : operands(operands) {}

// std::shared_ptr<Action> LoadAction::execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) { 
//     std::ifstream file;
//     auto path = operands["-path"][0];

//     file.open(path);
//     if(!file.is_open()){
//         throw std::invalid_argument("Invalid path or filename");
//     }

//     document = SaveLoadSerializer::load(path);

//     currentSlideIndex = 0;

// }


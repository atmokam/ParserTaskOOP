#include <iostream>
#include <stdexcept>
#include "Application/Application.hpp"
#include "Data/Slide.hpp"
#include "Data/Item.hpp"
#include "Data/Document.hpp"
#include "Director/Actions.hpp"
#include "Director/Director.hpp"
#include "Command.hpp"
#include "Renderer/Renderer.hpp"
#include "Serialization/SaveLoad.hpp"
#include "Serialization/Converter.hpp" 



Command::Command() : application(Application::getInstance()) {}

void AddCommand::execute() {  

    if(operands.find("-name") != operands.end()){
        // [TK] Slide should not be passed to the item, item should not be aware about its containing Slide
        std::shared_ptr<Item> item = createItem(application.getDirector()->getCurrentSlide(), application.getDirector()->getCurrentSlideNumber());
        // [TK] Item already created by the above line, why we need to recreate it again?
        application.getDirector()->doAction(std::make_shared<AddItem>(item, application.getDirector()->getCurrentSlideNumber()));
    }
    else if(operands.find("-slide") != operands.end()){
        // [TK] Need to generate unique ID: getCurrentSlideNumber() + 1 is wrong thing
        application.getDirector()->doAction(std::make_shared<AddSlide>(std::make_shared<Slide>(), application.getDirector()->getCurrentSlideNumber() + 1));
        application.getDirector()->nextSlide();
    }

}

std::shared_ptr<Item> AddCommand::createItem(const std::shared_ptr<Slide>& slide, const size_t currentSlideIndex) {


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

    // [TK] generateID() belongs to the document, Ids should be unique across whole document, because Item could be moved from one slide to another
    return std::make_shared<Item>(type, pos, bounds, color, slide->generateID(), lineDescriptor);

}

void RemoveCommand::execute() {
    if(operands.find("-id") != operands.end()){
        std::shared_ptr<Item> item = application.getDirector()->getCurrentSlide()->getItem(std::stoi(operands["-id"][0]));
        if (item == nullptr){
            return;
        }
        application.getDirector()->doAction(std::make_shared<RemoveItem>(item, application.getDirector()->getCurrentSlideNumber()));
    }
    else if(operands.find("-slide") != operands.end()){
        if(application.getDirector()->getDocument()->size() == 1){
            std::cout << "Cannot remove slide, only 1 left" << std::endl;
            
        } else {
            application.getDirector()->doAction(std::make_shared<RemoveSlide>(application.getDirector()->getCurrentSlide(), application.getDirector()->getCurrentSlideNumber())); // director has the slide it needs to remove
            application.getDirector()->previousSlide();
        }
    }

}


void ChangeCommand::execute() {
    std::shared_ptr<Item> item = std::make_shared<Item>(*application.getDirector()->getCurrentSlide()->getItem(std::stoi(operands["-id"][0])));

    if(operands.find("-pos") != operands.end()){ 
        item->setPosition(Converter::convertToPosition(operands["-pos"]));
    }
    // if(operands.find("-name") != operands.end())
    if(operands.find("-w") != operands.end() && operands.find("-h") != operands.end()){
        item->setBoundingRect(BoundingRect{Converter::convertToBoundingRect(operands["-w"][0], operands["-h"][0])}); 
    }
    if(operands.find("-lcolor") != operands.end()){
        item->setLineColor(Converter::convertToColor(operands["-lcolor"][0]));
    }
    if(operands.find("-fcolor") != operands.end()){
        item->setFillColor(Converter::convertToColor(operands["-fcolor"][0]));
    }
    if(operands.find("-lwidth") != operands.end()){
        item->setLineDescriptorWidth(std::stod(operands["-lwidth"][0]));
    }
    if(operands.find("-lstyle") != operands.end()){
        item->setLineDescriptorStyle(Converter::convertToLineType(operands["-lstyle"][0]));
    }

    application.getDirector()->doAction(std::make_shared<ChangeItem>(item, application.getDirector()->getCurrentSlideNumber()));
}


void SaveCommand::execute() {  // review document versioning
    SaveLoad serializer;
    // [TK] Serializer should get input stream, file creation is the job of the command
    serializer.save(application.getDirector()->getDocument(), operands["-path"][0] , operands["-filename"][0]);

}

void LoadCommand::execute() { 
    SaveLoad deserializer;
    std::shared_ptr<IDocument> document = deserializer.load(operands["-path"][0]);
    std::cout << "Loaded document with " << document->size() << " slides" << std::endl;
    application.getDirector()->setDocument(document);
    application.getDirector()->setCurrentSlideNumber(0);
    application.getDirector()->clearUndoRedoStack();
}

void DisplayCommand::execute() {
    if(operands.find("-id") != operands.end()){
        std::shared_ptr<Item> item = application.getDirector()->getCurrentSlide()->getItem(std::stoi(operands["-id"][0]));
        if (item == nullptr){
            return;
        }
        Renderer renderer;
        renderer.renderText(std::cout, item);
    }
    else{
        Renderer renderer;
        renderer.renderText(std::cout, application.getDirector()->getCurrentSlide(), application.getDirector()->getCurrentSlideNumber());
    }
}


void ListCommand::execute() {
    
    auto document = application.getDirector()->getDocument();
    size_t currentSlideIndex  = 0;
    for (const auto& slide : *document){
        std::cout << "Slide: " << currentSlideIndex << std::endl;
        for(const auto& item : *slide){
            std::cout << item.first << "\t";
        }
        currentSlideIndex++;
        std::cout << std::endl;
    }
    
}

void NextCommand::execute() {
    application.getDirector()->nextSlide();
}

void PrevCommand::execute() {
    application.getDirector()->previousSlide();
}

void UndoCommand::execute() {
    application.getDirector()->undo();
}

void RedoCommand::execute() {
    application.getDirector()->redo();
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

OperandsContainer Command::getOperands() const {
    return operands;
}

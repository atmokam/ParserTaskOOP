#include <iostream>
#include <stdexcept>
#include "Application/Application.hpp"
#include "Data/Slide.hpp"
#include "Data/ItemLeafBuilder.hpp"
#include "Data/Document.hpp"
#include "Director/Actions.hpp"
#include "Director/Director.hpp"
#include "Command.hpp"
#include "Renderer/Renderer.hpp"
#include "Serialization/SaveLoad.hpp"
#include "Serialization/Converter.hpp" 



Command::Command() : application(Application::getInstance()) {}

void AddCommand::execute() 
{  
    if(operands.find("-name") != operands.end()){
    
        size_t currentSlideIndex = application.getDirector()->getCurrentSlideIndex();
        std::shared_ptr<ItemLeaf> item = createItem();

        application.getDirector()->doAction(std::make_shared<AddItem>(item, currentSlideIndex));
    }
    else if(operands.find("-slide") != operands.end()){
        std::shared_ptr<Slide> slide = std::make_shared<Slide>();
        size_t currentSlideIndex = application.getDirector()->getCurrentSlideIndex();
        application.getDirector()->doAction(std::make_shared<AddSlide>(slide, currentSlideIndex));
        application.getDirector()->setCurrentSlideIndex(application.getDirector()->getCurrentSlideIndex() + 1);
    }

}

std::shared_ptr<ItemLeaf> AddCommand::createItem() 
{

    ItemLeafBuilder builder;


    Type type = Type{Converter::convertToType(operands["-name"])};
    builder.setType(type);

    Position pos = Position{Converter::convertToPosition(operands["-pos"])};
    builder.setPosition(pos);

    Dimentions bounds = Dimentions{Converter::convertToDimentions(operands["-w"][0], operands["-h"][0])};
    builder.setDimentions(bounds);
    
    Color color; LineDescriptor lineDescriptor;
    if(operands.find("-lcolor") != operands.end()){
        color.hexLineColor = Converter::convertToColor(operands["-lcolor"][0]);
        builder.setLineColor(color.hexLineColor);
    }
    if (operands.find("-fcolor") != operands.end()){
        color.hexFillColor = Converter::convertToColor(operands["-fcolor"][0]);
        builder.setFillColor(color.hexFillColor);
    }
    if (operands.find("-lwidth") != operands.end()){
        lineDescriptor.width = std::stod(operands["-lwidth"][0]);
        builder.setLineDescriptorWidth(lineDescriptor.width);
    }
    if (operands.find("-lstyle") != operands.end()){
        lineDescriptor.type = Converter::convertToLineType(operands["-lstyle"][0]);
        builder.setLineDescriptorStyle(lineDescriptor.type);
    }

    std::shared_ptr<ItemLeaf> item = builder.build();
    std::shared_ptr<IDocument> document = application.getDirector()->getDocument();
    item->setID(document->generateID());
    return item;

}

void RemoveCommand::execute() 
{
    std::shared_ptr<Slide> slide = application.getDirector()->getCurrentSlide();
    size_t currentSlideIndex = application.getDirector()->getCurrentSlideIndex();

    if(operands.find("-id") != operands.end()){

        std::shared_ptr<ItemBase> item = slide->getItem(std::stoi(operands["-id"][0]));
        if (item == nullptr){
            return;
        }
        application.getDirector()->doAction(std::make_shared<RemoveItem>(item, currentSlideIndex));
    }
    else if(operands.find("-slide") != operands.end()){
        if(application.getDirector()->getDocument()->size() == 1){
            std::cout << "Cannot remove slide, only 1 left" << std::endl;
            
        } else {
            application.getDirector()->doAction(std::make_shared<RemoveSlide>(slide, currentSlideIndex)); 
            application.getDirector()->setCurrentSlideIndex(currentSlideIndex - 1);
        }
    }

}


void ChangeCommand::execute() 
{
    std::shared_ptr<Slide> slide = application.getDirector()->getCurrentSlide();
    std::shared_ptr<ItemLeaf> item = std::make_shared<ItemLeaf>(slide->getItem(std::stoi(operands["-id"][0])));
    ItemLeafBuilder builder(item); // sets on item

    if(operands.find("-pos") != operands.end()){ 
        builder.setPosition(Converter::convertToPosition(operands["-pos"]));
    }
    if(operands.find("-w") != operands.end() && operands.find("-h") != operands.end()){
        builder.setDimentions(Dimentions{Converter::convertToDimentions(operands["-w"][0], operands["-h"][0])}); 
    }
    if(operands.find("-lcolor") != operands.end()){
        builder.setLineColor(Converter::convertToColor(operands["-lcolor"][0]));
    }
    if(operands.find("-fcolor") != operands.end()){
        builder.setFillColor(Converter::convertToColor(operands["-fcolor"][0]));
    }
    if(operands.find("-lwidth") != operands.end()){
        builder.setLineDescriptorWidth(std::stod(operands["-lwidth"][0]));
    }
    if(operands.find("-lstyle") != operands.end()){
        builder.setLineDescriptorStyle(Converter::convertToLineType(operands["-lstyle"][0]));
    }

    size_t currentSlideIndex = application.getDirector()->getCurrentSlideIndex();
    application.getDirector()->doAction(std::make_shared<ChangeItem>(item, currentSlideIndex));
}


void SaveCommand::execute() 
{ 
    SaveLoad serializer;
    std::ofstream file;

    file.open(operands["-path"][0] + operands["-filename"][0] + ".ppx");
    if(!file.is_open()){
        throw std::invalid_argument("Invalid path or filename");
    }

    serializer.save(application.getDirector()->getDocument(), file);
}

void LoadCommand::execute() 
{ 
    SaveLoad deserializer;
    std::shared_ptr<IDocument> document = deserializer.load(operands["-path"][0]);
    std::cout << "Loaded document with " << document->size() << " slides" << std::endl;
    application.getDirector()->setDocument(document);
    application.getDirector()->setCurrentSlideIndex(0);
    application.getDirector()->clearUndoRedoStack();
}

void DisplayCommand::execute() 
{
    // if(operands.find("-id") != operands.end()){
    //     std::shared_ptr<ItemBase> item = application.getDirector()->getCurrentSlide()->getItem(std::stoi(operands["-id"][0]));
    //     if (item == nullptr){
    //         return;
    //     }
    //     Renderer renderer;
    //     renderer.renderText(std::cout, item);
    // }
    // else{
    //     Renderer renderer;
    //     renderer.renderText(std::cout, application.getDirector()->getCurrentSlide(), application.getDirector()->getCurrentSlideIndex());
    // }
}


void ListCommand::execute() 
{
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

void NextCommand::execute() 
{
    size_t currentSlideIndex = application.getDirector()->getCurrentSlideIndex();
    application.getDirector()->setCurrentSlideIndex(currentSlideIndex + 1);
}

void PrevCommand::execute() 
{
    size_t currentSlideIndex = application.getDirector()->getCurrentSlideIndex();
    application.getDirector()->setCurrentSlideIndex(currentSlideIndex - 1);
}

void UndoCommand::execute() 
{
    application.getDirector()->undo();
}

void RedoCommand::execute() 
{
    application.getDirector()->redo();
}

void ExitCommand::execute() 
{
    application.callExit();
}




void Command::addOperandToOperands(std::string operand) 
{
    operands[operand];                           // in case of no value
}

void Command::addValueToOperands(std::string value, std::string operand) 
{
    operands[operand].push_back(value);
}


std::string Command::getName() const 
{
    return name;
}

void Command::setName(std::string name) 
{
    this->name = name;
}

OperandsContainer Command::getOperands() const 
{
    return operands;
}

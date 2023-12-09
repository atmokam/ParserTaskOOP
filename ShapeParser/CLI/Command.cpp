#include <iostream>
#include <stdexcept>
#include "Application/Application.hpp"
#include "Data/Slide.hpp"
#include "Data/Document.hpp"
#include "Director/Actions.hpp"
#include "Director/Director.hpp"
#include "Command.hpp"
#include "Serialization/SaveLoad.hpp"
#include "Serialization/Converter.hpp" 
#include "Renderer/ShapeBase.hpp"



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
    Attributes attributes; Geometry geometry;
    Converter converter;
    std::shared_ptr<IDocument> document = application.getDirector()->getDocument();
    Attributes defaultAttributes = document->getDefaultAttributes();

    Type type = Type{converter.convertToType(operands["-name"][0])};

    geometry.setPosition(Position{converter.convertToPosition(operands["-pos"])});
   
    geometry.setWidth(converter.convertToDimention(operands["-w"][0]));
    geometry.setHeight(converter.convertToDimention(operands["-h"][0]));
    
    attributes.setHexLineColor((operands.find("-lcolor") != operands.end()) ? 
    converter.convertToColor(operands["-lcolor"][0]) : defaultAttributes.getHexLineColor().value());
   
    attributes.setHexFillColor((operands.find("-fcolor") != operands.end()) ?
    converter.convertToColor(operands["-fcolor"][0]) : defaultAttributes.getHexFillColor().value());
    
    attributes.setLineWidth((operands.find("-lwidth") != operands.end()) ? 
    std::stod(operands["-lwidth"][0]) : defaultAttributes.getLineWidth().value());
    
    attributes.setLineType((operands.find("-lstyle") != operands.end())? 
    converter.convertToLineType(operands["-lstyle"][0]) : defaultAttributes.getLineType().value());
    
    

    std::shared_ptr<ItemLeaf> item = std::make_shared<ItemLeaf>(type, geometry, attributes, document->generateID());
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
    Converter converter;
    std::shared_ptr<Slide> slide = application.getDirector()->getCurrentSlide();
    std::shared_ptr<ItemBase> item = slide->getItem(std::stoi(operands["-id"][0]));

    Attributes attributes = item->getAttributes(); 
    Geometry geometry = item->getGeometry();
    std::shared_ptr<ItemBase> newItem;

    if(item->getType() == Type::Group) {
        newItem = std::make_shared<ItemGroup>(*(std::static_pointer_cast<ItemGroup>(item)));
    }
    else{
        newItem = std::make_shared<ItemLeaf>(*(std::static_pointer_cast<ItemLeaf>(item)));
    }


    //i need to create a temporary base

    if(operands.find("-pos") != operands.end()){ 
        geometry.setPosition(converter.convertToPosition(operands["-pos"]));
    }
    if(operands.find("-w") != operands.end() && operands.find("-h") != operands.end()){
        geometry.setWidth(converter.convertToDimention(operands["-w"][0])); 
        geometry.setHeight(converter.convertToDimention(operands["-h"][0]));
    }
    if(operands.find("-lcolor") != operands.end()){
        attributes.setHexLineColor(converter.convertToColor(operands["-lcolor"][0]));
    }
    if(operands.find("-fcolor") != operands.end()){
        attributes.setHexFillColor(converter.convertToColor(operands["-fcolor"][0]));
    }
    if(operands.find("-lwidth") != operands.end()){
        attributes.setLineWidth(std::stod(operands["-lwidth"][0]));
    }
    if(operands.find("-lstyle") != operands.end()){
        attributes.setLineType(converter.convertToLineType(operands["-lstyle"][0]));
    }
    newItem->setAttributes(attributes);
    newItem->setGeometry(geometry);
    

    size_t currentSlideIndex = application.getDirector()->getCurrentSlideIndex();
    application.getDirector()->doAction(std::make_shared<ChangeItem>(newItem, currentSlideIndex));
}


void SaveCommand::execute() 
{ 
    // SaveLoad serializer;
    // std::ofstream file;

    // file.open(operands["-path"][0] + operands["-filename"][0] + ".ppx");
    // if(!file.is_open()){
    //     throw std::invalid_argument("Invalid path or filename");
    // }

    // serializer.save(application.getDirector()->getDocument(), file);
}

void LoadCommand::execute() 
{ 
    // SaveLoad deserializer;
    // std::shared_ptr<IDocument> document = deserializer.load(operands["-path"][0]);
    // std::cout << "Loaded document with " << document->size() << " slides" << std::endl;
    // application.getDirector()->setDocument(document);
    // application.getDirector()->setCurrentSlideIndex(0);
    // application.getDirector()->clearUndoRedoStack();
}

void DisplayCommand::execute() 
{
    if(operands.find("-id") != operands.end()){
        std::shared_ptr<ItemBase> item = application.getDirector()->getCurrentSlide()->getItem(std::stoi(operands["-id"][0]));
        if (item == nullptr){
            return;
        }
        ShapeBase shape(item);
        shape.print(std::cout);
    }
    else{}
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

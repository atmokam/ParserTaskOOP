#include <iostream>
#include <stdexcept>
#include <QJsonDocument>
#include <QByteArray>
#include <QImage>
#include <QString>
#include "Application/Application.hpp"
#include "Command.hpp"
#include "Data/Slide.hpp"
#include "Data/Document.hpp"
#include "Director/Actions.hpp"
#include "Director/Director.hpp"
#include "Renderer/ShapeBase.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Formatting/DimentionConverter.hpp"
#include "Serialization/SaveLoad.hpp"
#include "Serialization/Converter.hpp" 



Command::Command() : application(App::Application::getInstance()) {}

void AddCommand::execute() 
{  
    if(operands.find("-name") != operands.end())
    {
        size_t currentSlideIndex = application.getDirector()->getCurrentSlideIndex();
        std::shared_ptr<ItemLeaf> item = createItem();
        application.getDirector()->doAction(std::make_shared<AddItem>(item, currentSlideIndex));
        application.getDocument()->setMaximumID(item->getID());
    }
    else if(operands.find("-slide") != operands.end())
    {
        std::shared_ptr<Slide> slide = std::make_shared<Slide>();
        size_t currentSlideIndex = application.getDirector()->getCurrentSlideIndex();
        application.getDirector()->doAction(std::make_shared<AddSlide>(slide, currentSlideIndex + 1));
        application.getDirector()->setCurrentSlideIndex(currentSlideIndex + 1);
    }
    application.getDirector()->setDocumentModified(true);

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
    
    return std::make_shared<ItemLeaf>(type, geometry, attributes, document->generateID());

}

void RemoveCommand::execute() 
{
    std::shared_ptr<Slide> slide = application.getDirector()->getCurrentSlide();
    size_t currentSlideIndex = application.getDirector()->getCurrentSlideIndex();


    if(operands.find("-id") != operands.end())
    {
        std::shared_ptr<ItemBase> item = slide->getItem(std::stoi(operands["-id"][0]));
        if (item == nullptr){
            return;
        }
        application.getDirector()->doAction(std::make_shared<RemoveItem>(item, currentSlideIndex));
    }
    else if(operands.find("-slide") != operands.end())
    {
        if(application.getDirector()->getDocument()->size() == 1)
        {
            std::ostream& out = application.getController()->getOutputStream() ;
            out << "Cannot remove slide, only 1 left" << std::endl;
            
        } 
        else 
        {
            application.getDirector()->doAction(std::make_shared<RemoveSlide>(slide, currentSlideIndex)); 
            application.getDirector()->setCurrentSlideIndex(currentSlideIndex - 1);
        }
    }
    application.getDirector()->setDocumentModified(true);

}


void ChangeCommand::execute() 
{
    Converter converter;
    std::shared_ptr<Slide> slide = application.getDirector()->getCurrentSlide();
    std::shared_ptr<ItemBase> item = slide->getItem(std::stoi(operands["-id"][0]));
    Attributes attributes = item->getAttributes(); 
    Geometry geometry = item->getGeometry();

    std::shared_ptr<ItemBase> newItem;

    (item->getType() == Type::Group) ? newItem = std::make_shared<ItemGroup>(*std::static_pointer_cast<ItemGroup>(item)) : 
    newItem = std::make_shared<ItemLeaf>(*std::static_pointer_cast<ItemLeaf>(item));
   

    if(operands.find("-pos") != operands.end())
    { 
        geometry.setPosition(converter.convertToPosition(operands["-pos"]));
    }

    if(operands.find("-w") != operands.end() && operands.find("-h") != operands.end())
    {
        geometry.setWidth(converter.convertToDimention(operands["-w"][0])); 
        geometry.setHeight(converter.convertToDimention(operands["-h"][0]));
    }

    if(operands.find("-lcolor") != operands.end())
    {
        attributes.setHexLineColor(converter.convertToColor(operands["-lcolor"][0]));
    }

    if(operands.find("-fcolor") != operands.end())
    {
        attributes.setHexFillColor(converter.convertToColor(operands["-fcolor"][0]));
    }

    if(operands.find("-lwidth") != operands.end())
    {
        attributes.setLineWidth(std::stod(operands["-lwidth"][0]));
    }

    if(operands.find("-lstyle") != operands.end())
    {
        attributes.setLineType(converter.convertToLineType(operands["-lstyle"][0]));
    }

    newItem->setAttributes(attributes);
    newItem->setGeometry(geometry);
    

    size_t currentSlideIndex = application.getDirector()->getCurrentSlideIndex();
    application.getDirector()->doAction(std::make_shared<ChangeItem>(newItem, currentSlideIndex));

    application.getDirector()->setDocumentModified(true);
}


void SaveCommand::execute() 
{ 
    std::shared_ptr<IDocument> document = application.getDirector()->getDocument();
    SaveLoad serializer;
    QJsonDocument documentJson;
    serializer.save(document, documentJson);
    QByteArray byteArray = documentJson.toJson();

    std::string path = operands["-path"][0] + operands["-filename"][0] + ".json";

    std::ifstream file (path);
    if(file.good())
    {
        std::ostream& out = application.getController()->getOutputStream();
        out << "File already exists, do you want to overwrite it? (y/n)" << std::endl;
        file.close();
        char answer;
        std::istream& in = application.getController()->getInputStream();
        in >> answer; 
        if(answer == 'n')
            return;
    }
   
    std::ofstream output (path);
    if(output.is_open())
    {
        output << byteArray.toStdString();
        output.close();
    }
    else
    {
        throw std::runtime_error("Could not open file");
    }

    application.getDirector()->setDocumentModified(false);

}

void LoadCommand::execute() 
{ 
    std::ifstream file;
    file.open(operands["-path"][0]);
    if(!file.is_open())
    {
        throw std::runtime_error("Could not open file");
    }
    std::string contents{std::istreambuf_iterator<char>{file}, std::istreambuf_iterator<char>{}};
    QJsonDocument content = QJsonDocument::fromJson(contents.c_str());
    file.close();
    SaveLoad deserializer;
    std::shared_ptr<IDocument> newDoc = std::make_shared<Document>();
    deserializer.load(content, newDoc);
    application.getDirector()->setDocument(newDoc);
    application.getDirector()->setCurrentSlideIndex(0);
    application.getDirector()->clearUndoRedoStack();
}



void DisplayCommand::execute() 
{
    if(operands.find("-id") != operands.end())
    {
        std::shared_ptr<Slide> current = application.getDirector()->getCurrentSlide();
        std::shared_ptr<ItemBase> item = current->getItem(std::stoi(operands["-id"][0]));
        if (item == nullptr)
        {
            return;
        }

        ShapeBase shape(item);
        shape.print(application.getController()->getOutputStream());
    }
    else
    {
        std::shared_ptr<Slide> current = application.getDirector()->getCurrentSlide();
        for(const auto& item : *current)
        {
            ShapeBase shape(item.second);
            std::ostream& out = application.getController()->getOutputStream() ;
            shape.print(out);
            out << std::endl;
        }
    }
}


void ListCommand::execute() 
{
    auto document = application.getDirector()->getDocument();

    size_t currentSlideIndex  = 0;
    for (const auto& slide : *document)
    {
        std::ostream& out = application.getController()->getOutputStream() ;
        out << "Slide: " << currentSlideIndex << std::endl;
        for(const auto& item : *slide){
            out << item.first << "\t";
        }
        currentSlideIndex++;
        out << std::endl;
    }
    
}



void NextCommand::execute() 
{
    size_t currentSlideIndex = application.getDirector()->getCurrentSlideIndex();
    if(currentSlideIndex < application.getDirector()->getDocument()->size() - 1)
        application.getDirector()->setCurrentSlideIndex(currentSlideIndex + 1);
}



void PrevCommand::execute() 
{
    size_t currentSlideIndex = application.getDirector()->getCurrentSlideIndex();
    if(currentSlideIndex > 0)
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
    if( application.getDirector()->isDocumentModified())
    {
        std::ostream& out = application.getController()->getOutputStream();
        out << "You have unsaved changes, are you sure you want to exit? (y/n)" << std::endl;
        char answer;
        std::istream& in = application.getController()->getInputStream();
        in >> answer;
        if(answer == 'n')
            return;
    }

    application.callExit();
    
}


void DrawCommand::execute() 
{
    DimentionConverter converter;
    std::shared_ptr<Slide> slide = application.getDirector()->getCurrentSlide();
    std::shared_ptr<IDocument> document = application.getDirector()->getDocument();
    auto format = document->getFormat();
    auto width = converter.toPixels(format.first); // only A4 format for now
    auto height = converter.toPixels(format.second);
    QImage image(width, height, QImage::Format_ARGB32_Premultiplied);
    Renderer renderer;
    renderer.draw(image, converter, slide);
    QString path = QString::fromStdString(operands["-path"][0] + operands["-filename"][0] + ".png");
    image.save(path);

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
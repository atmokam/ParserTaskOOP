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
#include "Director/IDirector.hpp"
#include "Renderer/ShapeBase.hpp"
#include "Renderer/ShapeLibrary.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Formatting/DimentionConverter.hpp"
#include "Serialization/SaveLoad.hpp"
#include "Serialization/Converter.hpp"

#include "Data/ItemBuilder.hpp"

namespace CLI {

    Command::Command() : application(App::Application::getInstance()) {}

    void AddCommand::execute() 
    {  
        if(operands.find("-name") != operands.end())
        {
            size_t currentSlideIndex = application.getDirector()->getCurrentSlideIndex();
            std::shared_ptr<Data::ItemLeaf> item = createItem();
            application.getDirector()->doAction(std::make_shared<Director::AddItem>(item, currentSlideIndex));
            application.getDocument()->getIDGenerator().addID(item->getID());
        }
        else if(operands.find("-slide") != operands.end())
        {
            std::shared_ptr<Data::Slide> slide = std::make_shared<Data::Slide>();
            size_t currentSlideIndex = application.getDirector()->getCurrentSlideIndex();
            application.getDirector()->doAction(std::make_shared<Director::AddSlide>(slide, currentSlideIndex + 1));
            application.getDirector()->setCurrentSlideIndex(currentSlideIndex + 1);
        }
        application.getDirector()->setDocumentModified(true);

    }

    std::shared_ptr<Data::ItemLeaf> AddCommand::createItem() 
    {
        Data::ItemBuilder builder;
        builder.buildItem(operands);
        return std::dynamic_pointer_cast<Data::ItemLeaf>(builder.getItem());

    }

    void RemoveCommand::execute() 
    {
        std::shared_ptr<Data::Slide> slide = application.getDirector()->getCurrentSlide();
        size_t currentSlideIndex = application.getDirector()->getCurrentSlideIndex();


        if(operands.find("-id") != operands.end())
        {
            std::shared_ptr<Data::ItemBase> item = slide->getItem(std::stoi(operands["-id"][0]));
            if (item == nullptr){
                return;
            }
            application.getDirector()->doAction(std::make_shared<Director::RemoveItem>(item, currentSlideIndex));
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
                application.getDirector()->doAction(std::make_shared<Director::RemoveSlide>(slide, currentSlideIndex)); 
                application.getDirector()->setCurrentSlideIndex(currentSlideIndex - 1);
            }
        }
        application.getDirector()->setDocumentModified(true);

    }


    void ChangeCommand::execute() 
    {
        Serialization::Converter converter;
        
        std::shared_ptr<Data::Slide> slide = application.getDirector()->getCurrentSlide();
       
        std::shared_ptr<Data::ItemBase> item = slide->getItem(std::stoi(operands["-id"][0]));
        std::shared_ptr<Data::ItemBase> newItem;
        if(item->getType() == Renderer::Type::Group)
        {
            newItem = std::make_shared<Data::ItemGroup>(*std::static_pointer_cast<Data::ItemGroup>(item));
        } 
        else
        {
            newItem = std::make_shared<Data::ItemLeaf>(*std::static_pointer_cast<Data::ItemLeaf>(item));
        }
        
        Data::ItemBuilder builder(newItem);
        builder.buildItem(operands);
        newItem = builder.getItem();

        size_t currentSlideIndex = application.getDirector()->getCurrentSlideIndex();
        application.getDirector()->doAction(std::make_shared<Director::ChangeItem>(newItem, currentSlideIndex));

        application.getDirector()->setDocumentModified(true);
    }


    void SaveCommand::execute() 
    { 
        std::shared_ptr<Data::IDocument> document = application.getDirector()->getDocument();
        Serialization::SaveLoad serializer;
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
        Serialization::SaveLoad deserializer;
        std::shared_ptr<Data::IDocument> newDoc = std::make_shared<Data::Document>();
        deserializer.load(content, newDoc);
        application.getDirector()->setDocument(newDoc);
        application.getDirector()->setCurrentSlideIndex(0);
        application.getDirector()->clearUndoRedoStack();
    }



    void DisplayCommand::execute() 
    {
        if(operands.find("-id") != operands.end())
        {
            std::shared_ptr<Data::Slide> current = application.getDirector()->getCurrentSlide();
            std::shared_ptr<Data::ItemBase> item = current->getItem(std::stoi(operands["-id"][0]));
            if (item == nullptr)
            {
                return;
            }

            Renderer::ShapeBase shape(item);
            shape.print(application.getController()->getOutputStream());
        }
        else
        {
            std::shared_ptr<Data::Slide> current = application.getDirector()->getCurrentSlide();
            Renderer::ShapeBase shape(current->getTopItem());
            std::ostream& out = application.getController()->getOutputStream() ;
            shape.print(out);
            out << std::endl;

        }
    }


    void ListCommand::execute() 
    {
        auto document = application.getDirector()->getDocument();

        size_t currentSlideIndex  = 0;
        for (const auto& slide : *document)
        {
            std::ostream& out = application.getController()->getOutputStream();
            out << "Slide: " << currentSlideIndex << std::endl;
            auto items = slide->getTopItem();
            for(const auto& item : *items)
            {
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
        Renderer::Formatting::DimentionConverter converter;
        std::shared_ptr<Data::Slide> slide = application.getDirector()->getCurrentSlide();
        std::shared_ptr<Data::IDocument> document = application.getDirector()->getDocument();
        auto format = document->getFormat();
        auto width = converter.toPixels(format.first); // only A4 format for now
        auto height = converter.toPixels(format.second);
        QImage image(width, height, QImage::Format_ARGB32_Premultiplied);
        Renderer::Renderer renderer;
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

}
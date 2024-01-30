#include <QJsonDocument>
#include <QByteArray>
#include <QImage>
#include <QString>
#include "Application/Application.hpp"
#include "Command.hpp"
#include "Data/Slide.hpp"
#include "Data/Document.hpp"
#include "Data/Item/ItemBuilder.hpp"
#include "Director/Actions.hpp"
#include "Renderer/VisualRendering.hpp"
#include "Renderer/ConsoleRendering.hpp"
#include "Renderer/Formatting/DimentionConverter.hpp"
#include "Serialization/Serializer.hpp"
#include "Serialization/Deserializer.hpp"
#include "Serialization/Converter.hpp"

namespace CLI 
{

    Command::Command() : application(App::Application::getInstance()), 
    out(application.get().getController()->getOutputStream()), 
    director(application.get().getDirector()){}


    void AddCommand::execute() 
    {  
        auto directorPtr = director.lock();
        if(operands.find("-name") != operands.end())
        {
            size_t currentSlideIndex = directorPtr->getCurrentSlideIndex();
            std::shared_ptr<Data::ItemLeaf> item = createItem();
            directorPtr->doAction(std::make_shared<Director::AddItem>(item, currentSlideIndex));
            auto document = application.get().getDocument();
            auto idGen = document->getIDGenerator();
            idGen->addID(item->getID());
        }
        else if(operands.find("-slide") != operands.end())
        {
            std::shared_ptr<Data::Slide> slide = std::make_shared<Data::Slide>();
            size_t currentSlideIndex = directorPtr->getCurrentSlideIndex();
            directorPtr->doAction(std::make_shared<Director::AddSlide>(slide, currentSlideIndex + 1));
            directorPtr->setCurrentSlideIndex(currentSlideIndex + 1);
        }
        directorPtr->setDocumentModified(true);

    }

    std::shared_ptr<Data::ItemLeaf> AddCommand::createItem() 
    {
        Data::ItemBuilder builder;
        builder.buildItemLeaf(operands);
        return std::dynamic_pointer_cast<Data::ItemLeaf>(builder.getItem());
    }



    void RemoveCommand::execute() 
    {
        auto directorPtr = director.lock();

        std::shared_ptr<Data::Slide> slide = directorPtr->getCurrentSlide();
        size_t currentSlideIndex = directorPtr->getCurrentSlideIndex();
        std::shared_ptr<Data::IDocument> document = directorPtr->getDocument();

        if(operands.find("-id") != operands.end())
        {
            std::shared_ptr<Data::ItemBase> item = slide->getItem(std::stoi(operands["-id"][0]));
            if (item == nullptr){
                return;
            }
            directorPtr->doAction(std::make_shared<Director::RemoveItem>(item, currentSlideIndex));
            auto document = application.get().getDocument();
            auto idGen = document->getIDGenerator();
            idGen->removeID(item->getID());
        }

        else if(operands.find("-slide") != operands.end())
        {
            if(directorPtr->getDocument()->size() == 1)
            {
                out.get() << "Cannot remove slide, only 1 left" << std::endl;
            } 
            else 
            {
                directorPtr->doAction(std::make_shared<Director::RemoveSlide>(slide, currentSlideIndex)); 
                directorPtr->setCurrentSlideIndex(currentSlideIndex - 1);
            }
        }
        directorPtr->setDocumentModified(true);

    }



    void ChangeCommand::execute() 
    {
        auto directorPtr = director.lock();

        bool isChanged = false;
        std::shared_ptr<Data::Slide> slide = directorPtr->getCurrentSlide();
        std::shared_ptr<Data::ItemBase> item = slide->getItem(std::stoi(operands["-id"][0]));
        size_t currentSlideIndex = directorPtr->getCurrentSlideIndex();

        Data::Attributes tempAttributes = item->getAttributes();
        Data::Geometry tempGeometry = item->getGeometry();

        if(item)            
        {
            Data::ID id = item->getID();
            Data::ItemBuilder builder;
            if(builder.trySetAttributes(operands, tempAttributes))
            {
                directorPtr->doAction(std::make_shared<Director::ChangeAttributes>(tempAttributes, id, currentSlideIndex));
                isChanged = true;
            }
            if(builder.trySetGeometry(operands, tempGeometry))
            {
                directorPtr->doAction(std::make_shared<Director::ChangeGeometry>(tempGeometry, id, currentSlideIndex));
                isChanged = true;
            }
        }

        directorPtr->setDocumentModified(isChanged);
    }

   
   



    void SaveCommand::execute() 
    { 
        std::string path = operands["-path"][0] + operands["-filename"][0] + ".json";        
        std::ofstream output (path);
        if(!output.is_open())
        {
            out.get() << "Could not open file" << std::endl;
        }

        auto directorPtr = director.lock();

        std::shared_ptr<Data::IDocument> document = directorPtr->getDocument();
        QJsonDocument documentJson;
       
        Serialization::Serializer serializer(documentJson);
        serializer.save(document);
        
        QByteArray byteArray = documentJson.toJson();
        output << byteArray.toStdString();
        output.close();

        directorPtr->setDocumentModified(false);
    }


    void LoadCommand::execute() 
    { 
        std::ifstream file;
        file.open(operands["-path"][0]);
        if(!file.is_open())
        {
           out.get() << "Could not open file" << std::endl;
        }
        
        auto directorPtr = director.lock();
        std::string contents{std::istreambuf_iterator<char>{file}, std::istreambuf_iterator<char>{}};
        QJsonDocument content = QJsonDocument::fromJson(contents.c_str());
        file.close();

        std::shared_ptr<Data::IDocument> newDoc = std::make_shared<Data::Document>();
        Serialization::Deserializer deserializer(newDoc);
        deserializer.load(content);

        directorPtr->setDocument(newDoc);
        directorPtr->setCurrentSlideIndex(0);
        directorPtr->clearUndoRedoStack();
    }



    void DisplayCommand::execute() 
    {
        auto directorPtr = director.lock();

        if(operands.find("-id") != operands.end())
        {
            std::shared_ptr<Data::Slide> currentSlide = directorPtr->getCurrentSlide();
            std::shared_ptr<Data::ItemBase> item = currentSlide->getItem(std::stoi(operands["-id"][0]));
            if (item == nullptr)
            {
                return;
            }
            Renderer::ConsoleRenderingVisitor visitor(out.get());
            visitor.print(item);
           
        }
        else
        {
            std::shared_ptr<Data::Slide> currentSlide = directorPtr->getCurrentSlide();
            Renderer::ConsoleRenderingVisitor visitor(out.get());
            visitor.print(currentSlide);

        }
    }


    void ListCommand::execute() 
    {
        auto directorPtr = director.lock();

        auto document = directorPtr->getDocument();

        size_t currentSlideIndex  = 0;
        for (const auto& slide : *document)
        {
            
            out.get() << "Slide: " << currentSlideIndex << std::endl;
            auto items = slide->getTopItem();
            for(const auto& item : *items)
            {
               out.get() << item.first << "\t";
            }

            currentSlideIndex++;
            out.get() << std::endl;
        }
        
    }



    void NextCommand::execute() 
    {
        auto directorPtr = director.lock();

        size_t currentSlideIndex = directorPtr->getCurrentSlideIndex();
        if(currentSlideIndex < directorPtr->getDocument()->size() - 1)
            directorPtr->setCurrentSlideIndex(currentSlideIndex + 1);
    }



    void PrevCommand::execute() 
    {
        auto directorPtr = director.lock();

        size_t currentSlideIndex = directorPtr->getCurrentSlideIndex();
        if(currentSlideIndex > 0)
            directorPtr->setCurrentSlideIndex(currentSlideIndex - 1);
    }



    void UndoCommand::execute() 
    {
        auto directorPtr = director.lock();
        directorPtr->undo();
    }



    void RedoCommand::execute() 
    {
        auto directorPtr = director.lock();
        directorPtr->redo();
    }



    void ExitCommand::execute()    
    {
        if( operands.find("-force") != operands.end())
        {
            application.get().quit();
            return;
        }

        auto directorPtr = director.lock();

        if( directorPtr->isDocumentModified())
        {
            out.get() << "You have unsaved changes, please save them before exit." << std::endl;
            return;
        }

        application.get().quit();
        
    }


    void DrawCommand::execute() 
    {
        auto directorPtr = director.lock();

        Renderer::Formatting::DimentionConverter converter;
        std::shared_ptr<Data::Slide> slide = directorPtr->getCurrentSlide();
        std::shared_ptr<Data::IDocument> document = directorPtr->getDocument();
        auto format = document->getFormat();
        auto width = converter.toPixels(format.first); // default A4 format for now
        auto height = converter.toPixels(format.second);
        QImage image(width, height, QImage::Format_ARGB32_Premultiplied);
        image.fill(Qt::white);

        Renderer::VisualRenderingVisitor visitor(image, converter);
        visitor.draw(slide);
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
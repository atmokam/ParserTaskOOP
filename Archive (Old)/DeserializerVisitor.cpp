#include "DeserializerVisitor.hpp"
#include "JsonConverter.hpp"
#include "Data/IDGenerator.hpp"
#include "Data/Item/ItemBase.hpp"
#include "Data/Slide.hpp"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

namespace Serialization
{

    DeserializerVisitor::DeserializerVisitor(std::shared_ptr<Data::IDocument>& output) {}


    void DeserializerVisitor::deserializeHelper(QJsonValueRef& value)
    {
        std::shared_ptr<Data::ItemBase> newItem = nullptr;
        if(value.isArray())
        {
            newItem = std::make_shared<Data::ItemGroup>();
        }
        else
        {
            newItem = std::make_shared<Data::ItemLeaf>();
        }
        
        newItem->accept(std::make_shared<DeserializerVisitor>(*this));
        auto slide = *std::prev(docOutput->end());
        slide->addItem(newItem);
    }

    void DeserializerVisitor::visit(Data::ItemLeaf& item)
    {
        
    }

    void DeserializerVisitor::visit(Data::ItemGroup& item)
    {
        auto group = value->toArray();
        for(auto item: group)
        {
            deserializeHelper(item);
        }
    }


    void DeserializerVisitor::load(QJsonDocument& document)
    {
        JsonConverter converter;        
        QJsonObject documentObject = document.object();
        QJsonArray slidesArray = documentObject["slides"].toArray();
    
        for(auto slide: slidesArray) 
        {
            deserializeHelper(slide);
            docOutput->addSlide(std::make_shared<Data::Slide>());
        }

        docOutput->getIDGenerator()->setIDs(converter.convertToIDs(documentObject["IDs"].toArray()));
        docOutput->setFormat(converter.convertToFormat(documentObject["format"].toArray()));
        
    }

    
}
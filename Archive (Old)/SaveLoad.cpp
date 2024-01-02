#include "SaveLoad.hpp"
#include "Data/Document.hpp"
#include "Data/Slide.hpp"
#include "JsonConverter.hpp"
#include "Data/Item/ItemBase.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

namespace Serialization
{
    void SaveLoad::save(const std::shared_ptr<Data::IDocument>& document, QJsonDocument& stream)
    {
        QJsonArray documentArray;
        JsonConverter converter;
        for (auto slide : *document)
        {
            QJsonArray slideArray;
            auto items = slide->getTopItem();
            for(auto& item: *items)
            {
                recursiveSerialize(item.second, slideArray);
            }
            documentArray.append(slideArray);
        }
        QJsonObject documentObject;
        documentObject["slides"] = documentArray;
        documentObject["IDs"] = converter.convertToJson(document->getIDGenerator().getIDs());
        documentObject["format"] = converter.convertToJson(document->getFormat());
        stream.setObject(documentObject);
    }

    void SaveLoad::recursiveSerialize(const std::shared_ptr<Data::ItemBase>& item, QJsonArray& slideArray)  // attribs and geometry for groups?
    {
        if(auto group = std::dynamic_pointer_cast<Data::ItemGroup>(item))
        {
            
            for(auto& [_, subItem]: *group)
            {
                recursiveSerialize(subItem, slideArray);
            }   
        }
        else if(auto leaf = std::dynamic_pointer_cast<Data::ItemLeaf>(item))
        {
            slideArray.append(serializeLeaf(leaf));
        }
        
    }

    QJsonObject SaveLoad::serializeLeaf(const std::shared_ptr<Data::ItemLeaf>& item)
    {
        JsonConverter converter;
        QJsonObject itemObject;
        itemObject["id"] = item->getID();
        itemObject["type"] = converter.convertToJson(item->getType());
        itemObject["attributes"] = converter.convertToJson(item->getAttributes());
        itemObject["geometry"] = converter.convertToJson(item->getGeometry());
        
        return itemObject;
    }


    void SaveLoad::load(QJsonDocument& stream, const std::shared_ptr<Data::IDocument>& document)
    {    
        QJsonObject documentObject = stream.object();
        JsonConverter converter;
    

        document->getIDGenerator().setIDs(converter.convertToIDs(documentObject["IDs"].toArray()));
        document->setFormat(converter.convertToFormat(documentObject["format"].toArray()));
        
        QJsonArray documentArray = documentObject["slides"].toArray();
    
        size_t counter = 0;
        for(auto slide: documentArray)
        {
            std::shared_ptr<Data::Slide> newSlide = std::make_shared<Data::Slide>();
            QJsonArray slideArray = slide.toArray();
            for(auto item: slideArray)
            {
                recursiveDeserialize(item, newSlide);
            }
            document->addSlide(newSlide, counter++);
        
        }

        
    }

    void SaveLoad::recursiveDeserialize(QJsonValueRef& item, const std::shared_ptr<Data::Slide>& slide)
    {
        if(item.isArray())
        {
            auto array = item.toArray();
            for(auto subItem: array)
            {
                recursiveDeserialize(subItem, slide);
            }
        }
        else if(item.isObject())
        {
            
            slide->addItem(deserializeLeaf(item.toObject()));
        }
        
    }

    std::shared_ptr<Data::ItemLeaf> SaveLoad::deserializeLeaf(const QJsonObject& object)
    {
        JsonConverter converter;
        std::shared_ptr<Data::ItemLeaf> item = std::make_shared<Data::ItemLeaf>();
        item->setID(object["id"].toInt());
        item->setType(converter.convertToType(object["type"]));
        
        Data::Attributes attributes = converter.convertToAttributes(object["attributes"]);
        item->setAttributes(attributes);
    
        Data::Geometry geometry = converter.convertToGeometry(object["geometry"]);
        item->setGeometry(geometry);
        
        return item;
    }
}
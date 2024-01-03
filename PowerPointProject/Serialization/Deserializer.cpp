#include "Deserializer.hpp"
#include "Include/IDocument.hpp"
#include "Data/IDGenerator.hpp"
#include "Data/Slide.hpp"
#include "Data/Item/ItemBase.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>


#include "JsonConverter.hpp"

namespace Serialization
{
    Deserializer::Deserializer(std::shared_ptr<Data::IDocument>& output): docOutput(output)
    {}

    void Deserializer::load(QJsonDocument& document)
    {
        JsonConverter converter;        
        QJsonObject documentObject = document.object();
        QJsonArray slidesArray = documentObject["slides"].toArray();
    
        for(auto slide: slidesArray) 
        {
            deserialize(slide.toArray());
            docOutput->addSlide(std::make_shared<Data::Slide>());
        }

        docOutput->getIDGenerator()->setIDs(converter.convertToIDs(documentObject["IDs"].toArray()));
        docOutput->setFormat(converter.convertToFormat(documentObject["format"].toArray()));
    }

    void Deserializer::deserialize(QJsonArray array)
    {
        for(auto item: array)
        {
            if(item.isArray())
            {
                deserialize(item.toArray());
            }
            else
            {
                deserialize(item.toObject());
            }
        }
    }

    void Deserializer::deserialize(QJsonObject object)
    {
        JsonConverter converter;
        std::shared_ptr<Data::ItemLeaf> item = std::make_shared<Data::ItemLeaf>();
        item->setID(object["id"].toInt());
        item->setType(converter.convertToType(object["type"]));
        
        Data::Attributes attributes = converter.convertToAttributes(object["attributes"]);
        item->setAttributes(attributes);
    
        Data::Geometry geometry = converter.convertToGeometry(object["geometry"]);
        item->setGeometry(geometry);

        auto slide = *std::prev(docOutput->end());
        slide->addItem(item);
    }
}


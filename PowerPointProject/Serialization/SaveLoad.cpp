#include "SaveLoad.hpp"
#include "Data/Document.hpp"
#include "Data/Slide.hpp"
#include "Converter.hpp"
#include "Data/ItemBase.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

void SaveLoad::save(const std::shared_ptr<IDocument>& document, QJsonDocument& stream)
{
    QJsonArray documentArray;
    Converter converter;
    for (auto slide : *document)
    {
        QJsonArray slideArray;
        for(auto& [_, subItem]: *slide)
        {
            recursiveSerialize(subItem, slideArray);
        }   
        documentArray.append(slideArray);
    }
    QJsonObject documentObject;
    documentObject["slides"] = documentArray;
    documentObject["maxID"] = converter.convertToJson(document->getMaximumID());
    documentObject["format"] = converter.convertToJson(document->getFormat());
    stream.setObject(documentObject);
}

void SaveLoad::recursiveSerialize(const std::shared_ptr<ItemBase>& item, QJsonArray& slideArray)
{
    if(auto group = std::dynamic_pointer_cast<ItemGroup>(item))
    {
        for(auto& [_, subItem]: *group)
        {
            recursiveSerialize(subItem, slideArray);
        }   
    }
    else if(auto leaf = std::dynamic_pointer_cast<ItemLeaf>(item))
    {
        slideArray.append(serializeLeaf(leaf));
    }
    
}

QJsonObject SaveLoad::serializeLeaf(const std::shared_ptr<ItemLeaf>& item)
{
    Converter converter;
    QJsonObject itemObject;
    itemObject["id"] = item->getID();
    itemObject["type"] = converter.convertToJson(item->getType());
    itemObject["attributes"] = converter.convertToJson(item->getAttributes());
    itemObject["geometry"] = converter.convertToJson(item->getGeometry());
    
    return itemObject;
}


void SaveLoad::load(QJsonDocument& stream, const std::shared_ptr<IDocument>& document)
{    
    QJsonObject documentObject = stream.object();
    Converter converter;
    std::cout << "loading load" << std::endl;

    document->setMaximumID(documentObject["maxID"].toInt());
    document->setFormat(converter.convertToFormat(documentObject["format"].toArray()));
    std::cout << "format set" << std::endl;
    QJsonArray documentArray = documentObject["slides"].toArray();
    std::cout << "array set" << std::endl;
    size_t counter = 0;
    for(auto slide: documentArray)
    {
        std::shared_ptr<Slide> newSlide = std::make_shared<Slide>();
        QJsonArray slideArray = slide.toArray();
        for(auto item: slideArray)
        {
            recursiveDeserialize(item, newSlide);
        }
        document->addSlide(newSlide, counter++);
       
    }

    
}

void SaveLoad::recursiveDeserialize(QJsonValueRef& item, const std::shared_ptr<Slide>& slide)
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

std::shared_ptr<ItemLeaf> SaveLoad::deserializeLeaf(const QJsonObject& object)
{
    Converter converter;
    std::shared_ptr<ItemLeaf> item = std::make_shared<ItemLeaf>();
    item->setID(object["id"].toInt());
    item->setType(converter.convertToType(object["type"].toString().toStdString()));
    Attributes attributes = converter.convertToAttributes(object["attributes"]);
    item->setAttributes(attributes);
    Geometry geometry = converter.convertToGeometry(object["geometry"]);
    item->setGeometry(geometry);
    return item;
}
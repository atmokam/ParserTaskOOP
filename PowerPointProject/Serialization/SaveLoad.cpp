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


std::shared_ptr<IDocument> SaveLoad::load(QJsonDocument& stream, const std::shared_ptr<IDocument>& document)
{
    
    

}

#include "SaveLoad.hpp"
#include "Data/Document.hpp"
#include "Data/Slide.hpp"
#include "Converter.hpp"
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
       documentArray.append(serialize(slide));
    }
    QJsonObject documentObject;
    documentObject["slides"] = documentArray;
    documentObject["maxID"] = converter.convertToJson(document->getMaximumID());
    documentObject["format"] = converter.convertToJson(document->getFormat());
    stream.setObject(documentObject);
}

QJsonArray SaveLoad::serialize(const std::shared_ptr<Slide>& slide)
{
    QJsonArray slideArray;
    Converter converter;
    for(auto& item: *slide)
    {
        QJsonObject itemObject;
        itemObject["id"] = item.first;
        itemObject["type"] = converter.convertToJson(item.second->getType());
        itemObject["attributes"] = converter.convertToJson(item.second->getAttributes());
        itemObject["geometry"] = converter.convertToJson(item.second->getGeometry());
        slideArray.append(itemObject);        
    }
    
    return slideArray;
    
}


std::shared_ptr<IDocument> SaveLoad::load(QJsonDocument& stream, const std::shared_ptr<IDocument>& document)
{
    

}

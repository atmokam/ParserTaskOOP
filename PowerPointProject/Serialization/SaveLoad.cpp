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
    QJsonObject documentObject;
    size_t slideIndex = 0;
    for (auto slide : *document)
    {
       documentObject[QString("slide ") + QString::number(slideIndex)] = serialize(slide);
    }
    stream.setObject(documentObject);
}

QJsonArray SaveLoad::serialize(const std::shared_ptr<Slide>& slide)
{
    QJsonArray slideObject;
    Converter converter;
    for(auto& item: *slide)
    {
        QJsonObject itemObject;
        itemObject["id"] = item.first;
        itemObject["type"] = converter.convertToJson(item.second->getType());
        itemObject["attributes"] = converter.convertToJson(item.second->getAttributes());
        itemObject["geometry"] = converter.convertToJson(item.second->getGeometry());
        slideObject.append(itemObject);        

    }
    
    return slideObject;
    
}


std::shared_ptr<IDocument> SaveLoad::load(const std::string& path)
{

}
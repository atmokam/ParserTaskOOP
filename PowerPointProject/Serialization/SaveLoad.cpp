#include "SaveLoad.hpp"
#include "Data/Document.hpp"
#include "Data/Slide.hpp"
#include "Converter.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

void SaveLoad::save(const std::shared_ptr<IDocument>& document, QJsonDocument& stream)
{
    QJsonObject documentObject;
    size_t slideIndex = 0;
    for (auto slide : *document)
    {
       documentObject["slide " + slideIndex] = serialize(slide, stream);
    }
}

QJsonObject SaveLoad::serialize(const std::shared_ptr<Slide>& slide, QJsonDocument& stream)
{
    QJsonObject slideObject;
    Converter converter;
    for(auto& item: *slide)
    {
        QJsonObject itemObject;
        itemObject["id"] = item.first;
        itemObject["type"] = converter.convertToJson(item.second->getType());
        itemObject["attributes"] = converter.convertToJson(item.second->getAttributes());
        itemObject["geometry"] = converter.convertToJson(item.second->getGeometry());        

    }
    
    return slideObject;
    
}


std::shared_ptr<IDocument> SaveLoad::load(const std::string& path){}
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
    for(auto& item: *slide)
    {
        QJsonObject itemObject;
       // to implement

    }
    
}


std::shared_ptr<IDocument> SaveLoad::load(const std::string& path){}
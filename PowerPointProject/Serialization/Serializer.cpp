#include "Serializer.hpp"
#include "Data/IDGenerator.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>



namespace Serialization
{
    
    Serializer::Serializer(QJsonDocument& output): output(output),
        currentSlideArray(std::make_shared<QJsonArray>())
    {}

    void Serializer::visit(Data::ItemLeaf& item)
    {
        JsonConverter converter;
        QJsonObject itemObject;
        itemObject["id"] = item.getID();
        itemObject["type"] = converter.convertToJson(item.getType());
        itemObject["attributes"] = converter.convertToJson(item.getAttributes());
        itemObject["geometry"] = converter.convertToJson(item.getGeometry());

        currentSlideArray->append(itemObject);
    }

    void Serializer::visit(Data::ItemGroup& item)
    {
        for(auto& [_, subItem]: item)
        {
            subItem->accept(*this);
        } 
    }

    void Serializer::save(const std::shared_ptr<Data::IDocument>& document)
    {
        JsonConverter converter;
        QJsonArray slidesArray;
        for(auto& slide: *document)
        {
            auto items = slide->getTopItem();
            items->accept(*this);
            slidesArray.append(*currentSlideArray);
            currentSlideArray.reset();
        }

        QJsonObject documentObject;
        documentObject["slides"] = slidesArray;
        documentObject["IDs"] = converter.convertToJson(document->getIDGenerator()->getIDs());
        documentObject["format"] = converter.convertToJson(document->getFormat());

        output.get().setObject(documentObject);
    }

}
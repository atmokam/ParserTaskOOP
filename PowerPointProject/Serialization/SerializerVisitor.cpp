#include "SerializerVisitor.hpp"
#include "Data/IDGenerator.hpp"
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>



namespace Serialization
{
    
    SerializerVisitor::SerializerVisitor(QJsonDocument& output): output(output),
        currentSlideArray(std::make_shared<QJsonArray>()), converter(std::make_unique<JsonConverter>())
    {}

    void SerializerVisitor::visit(Data::ItemLeaf& item)
    {
        QJsonObject itemObject;
        itemObject["id"] = item.getID();
        itemObject["type"] = converter->convertToJson(item.getType());
        itemObject["attributes"] = converter->convertToJson(item.getAttributes());
        itemObject["geometry"] = converter->convertToJson(item.getGeometry());
        currentSlideArray->append(itemObject);
    }

    void SerializerVisitor::visit(Data::ItemGroup& item)
    {
        for(auto& [_, subItem]: item)
        {
            subItem->accept(std::make_shared<SerializerVisitor>(*this));
        } 
    }

    void SerializerVisitor::save(const std::shared_ptr<Data::IDocument>& document)
    {
        QJsonArray slidesArray;
        for(auto& slide: *document)
        {
            auto items = slide->getTopItem();
            items->accept(std::make_shared<SerializerVisitor>(*this));
            slidesArray.append(*currentSlideArray);
            currentSlideArray = std::make_shared<QJsonArray>();
        }

        QJsonObject documentObject;
        documentObject["slides"] = slidesArray;
        documentObject["IDs"] = converter->convertToJson(document->getIDGenerator().getIDs());
        documentObject["format"] = converter->convertToJson(document->getFormat());
        output.get().setObject(documentObject);
    }

}
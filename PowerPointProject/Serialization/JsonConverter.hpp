#ifndef JSONCONVERTER_HPP
#define JSONCONVERTER_HPP

#include <utility>
#include "Data/ItemAttributes.hpp"


class QJsonValue;
class QJsonArray;

namespace Renderer
{
    enum class Type;
}

namespace Serialization
{
    class JsonConverter {
    public:
        JsonConverter() = default;
        QJsonValue convertToJson(const Data::Attributes& attribute);
        QJsonValue convertToJson(const Data::Geometry& geometry);
        QJsonArray convertToJson(const Data::Position& position); // could be done with the convertToIDs
        QJsonArray convertToJson(const std::pair<double, double>& format);
        QJsonValue convertToJson(const Renderer::Type& type);
        QJsonValue convertToJson(const Data::LineType& lineType);
        QJsonValue convertToJson(const long& color);
        QJsonValue convertToJson(const std::vector<Data::ID>& ids);

        Data::Attributes convertToAttributes(const QJsonValue& value);
        Data::Geometry convertToGeometry(const QJsonValue& value);
        Data::Position convertToPosition(const QJsonArray& array);
        std::pair<double, double> convertToFormat(const QJsonArray& array);
        Renderer::Type convertToType(const QJsonValue& value);
        Data::LineType convertToLineType(const QJsonValue& value);
        long convertToColor(const QJsonValue& value);
        std::vector<Data::ID> convertToIDs(const QJsonValue& value);    
    };
}
#endif
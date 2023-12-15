#ifndef JSONCONVERTER_HPP
#define JSONCONVERTER_HPP

#include <utility>
#include "Data/ItemAttributes.hpp"

class Attributes;
class Geometry;
class Position;



class QJsonValue;
class QJsonArray;

class JsonConverter {
public:
    JsonConverter() = default;
    QJsonValue convertToJson(const Attributes& attribute);
    QJsonValue convertToJson(const Geometry& geometry);
    QJsonArray convertToJson(const Position& position);
    QJsonArray convertToJson(const std::pair<double, double>& format);
    QJsonValue convertToJson(const Type& type);
    QJsonValue convertToJson(const LineType& lineType);
    QJsonValue convertToJson(const long& color);

    Attributes convertToAttributes(const QJsonValue& value);
    Geometry convertToGeometry(const QJsonValue& value);
    Position convertToPosition(const QJsonArray& array);
    std::pair<double, double> convertToFormat(const QJsonArray& array);
    Type convertToType(const QJsonValue& value);
    LineType convertToLineType(const QJsonValue& value);
    long convertToColor(const QJsonValue& value);    
};

#endif
#include "Converter.hpp"
#include "Data/ItemAttributes.hpp"
#include "Application/Application.hpp"
#include <sstream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>



Converter::Converter() { // move to shapelibrary
    typeMap = {
        {"line", Type::Line},
        {"rectangle", Type::Rectangle},
        {"trapezoid", Type::Trapezoid},
        {"ellipse", Type::Ellipse},
        {"triangle", Type::Triangle},
        {"group", Type::Group}
    };
}



Position Converter::convertToPosition(const std::vector<std::string>& values) {
    std::vector<double> result;
    for (auto value : values) {
        result.push_back(std::stod(value));
    }
    return Position{result};
}

Position Converter::convertToPosition(const std::string& str, const char delimiter) {
    std::vector<double> result;
    auto it = std::find(str.begin(), str.end(), delimiter);
    decltype(it) prev = str.begin();     
    while(it != str.end()){
        result.push_back(std::stod(std::string(prev, it)));
        prev = it + 1;
        it = std::find(prev, str.end(), delimiter);
    }

    result.push_back(std::stod(std::string(prev, it)));
    return Position{result};
}

Type Converter::convertToType(const std::string& value) {
    auto it = typeMap.find(value);
    return Type{it->second};
}

ID Converter::convertToID(const std::string& value) {
    return ID{std::stoi(value)};
}

double Converter::convertToDimention(const std::string& value) {
    return std::stod(value);
}

long Converter::convertToColor(const std::string& color) {
    long converted = std::stol(color.substr(1), nullptr, 16);    
    return converted;
}

LineType Converter::convertToLineType(const std::string& lineType) {
    if (lineType == "solid") {
        return LineType::Solid;
    } else if (lineType == "dashed") {
        return LineType::Dashed;
    } else if (lineType == "dotted") {
        return LineType::Dotted;
    } 
}


// convert to json

QJsonArray Converter::convertToJson(const Position& position) {
    QJsonArray result = QJsonArray();
    std::vector<double> values = position.getCoordinates();
    for (auto value : values) {
        result.append(value);
    }
    return result;
}

QJsonValue Converter::convertToJson(const Type& type) {
    switch (type) {
         case Type::Line:
            return QJsonValue("line");
        case Type::Rectangle:
            return QJsonValue("rectangle");
        case Type::Trapezoid:
            return QJsonValue("trapezoid");
        case Type::Ellipse:
            return QJsonValue("ellipse");
        case Type::Triangle:
            return QJsonValue("triangle");
        case Type::Group:
            return QJsonValue("group");
        default:
            return QJsonValue("");
    }
}

QJsonValue Converter::convertToJson(const LineType& lineType) 
{
    switch (lineType) {
        case LineType::Solid:
            return QJsonValue("solid");
        case LineType::Dashed:
            return QJsonValue("dashed");
        case LineType::Dotted:
            return QJsonValue("dotted");
        default:
            return QJsonValue("");
    }
}


QJsonValue Converter::convertToJson(const long& color) 
{
    std::stringstream stream;
    stream << "#" << std::hex << color;
    return QJsonValue(QString::fromStdString(stream.str()));
}


QJsonValue Converter::convertToJson(const Attributes& attribute) 
{
    Application& app = Application::getInstance();
    Attributes defaultAttributes = app.getDocument()->getDefaultAttributes();
    QJsonObject result;

    result["lineWidth"] = attribute.getLineWidth().has_value() ? 
    attribute.getLineWidth().value() : defaultAttributes.getLineWidth().value();   

    result["lineType"] = convertToJson(attribute.getLineType().has_value() ? 
    attribute.getLineType().value() : defaultAttributes.getLineType().value());

    result["lineColorHex"] = convertToJson(attribute.getHexLineColor().has_value() ?
    attribute.getHexLineColor().value() : defaultAttributes.getHexLineColor().value());

    result["fillColorHex"] = convertToJson(attribute.getHexFillColor().has_value() ? 
    attribute.getHexFillColor().value() : defaultAttributes.getHexFillColor().value());

    return result;
}


QJsonValue Converter::convertToJson(const Geometry& geometry) 
{
    QJsonObject result;

    result["position"] = convertToJson(geometry.getPosition().has_value() ?
    geometry.getPosition().value() : Position{});

    result["width"] = geometry.getWidth().has_value() ?
    geometry.getWidth().value() : 0;

    result["height"] = geometry.getHeight().has_value() ?
    geometry.getHeight().value() : 0;


    return result;
}

QJsonArray Converter::convertToJson(const std::pair<double, double>& format)
{
    QJsonArray result;
    result.append(format.first);
    result.append(format.second);
    return result;
}

// convert from json

Attributes Converter::convertToAttributes(const QJsonValue& value) 
{
    Attributes result;
    QJsonObject object = value.toObject();
    if (object.contains("lineWidth")) {
        result.setLineWidth(object["lineWidth"].toDouble());
    }
    if (object.contains("lineType")) {
        result.setLineType(convertToLineType(object["lineType"].toString().toStdString()));
    }
    if (object.contains("lineColorHex")) {
        result.setHexLineColor(convertToColor(object["lineColorHex"].toString().toStdString()));
    }
    if (object.contains("fillColorHex")) {
        result.setHexFillColor(convertToColor(object["fillColorHex"].toString().toStdString()));
    }
    return result;
}

Position Converter::convertToPosition(const QJsonArray& array)
{
    std::vector<double> result;
    for (auto value : array) {
        result.push_back(value.toDouble());
    }
    return Position{result};
}


Geometry Converter::convertToGeometry(const QJsonValue& value) 
{
    Geometry result;
    QJsonObject object = value.toObject();
    if (object.contains("position")) {
        result.setPosition(convertToPosition(object["position"].toArray()));
       
    }
    if (object.contains("width")) {
        result.setWidth(object["width"].toDouble());
       
    }
    if (object.contains("height")) {
        result.setHeight(object["height"].toDouble());
    }
    return result;
}


std::pair<double, double> Converter::convertToFormat(const QJsonArray& array)
{
    return std::make_pair(array[0].toDouble(), array[1].toDouble());
}


#include "Converter.hpp"
#include "Data/ItemAttributes.hpp"
#include "Application/Application.hpp"
#include "Renderer/ShapeLibrary.hpp"
#include <sstream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>


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
    ShapeLibrary shapeLibrary;
    return shapeLibrary.getType(value).value(); 
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
    } else {
        return LineType::None;
    }
}

std::string Converter::convertToString(const Position& position) {
    std::stringstream result;
    for (auto value : position.getCoordinates()) {
        result << value << " ";
    }
    return result.str();
}

std::string Converter::convertToString(const Type type)
{
    ShapeLibrary shapeLibrary;
    return shapeLibrary.getString(type);
}

std::string Converter::convertToString(const LineType line)
{
    switch(line)
    {
        case LineType::Dashed:
            return "dashed";
        case LineType::Dotted:
            return "dotted";
        case LineType::Solid:
            return "solid";
        default:
            return "none";
    }
}


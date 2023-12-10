#include "Converter.hpp"
#include <QJsonArray>
#include <QJsonObject>



Converter::Converter() { // shapelibrary
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
    } else {
        throw std::invalid_argument("Invalid line type");
    }
}


QJsonArray Converter::convertToArray(const Position& position) {
    QJsonArray result;
    std::vector<double> values = position.getCoordinates();
    for (auto value : values) {
        result.append(value);
    }
    return result;
}

std::string Converter::convertToString(const Type& type) {
    switch (type) {
        case Type::Line:
            return "line";
        case Type::Rectangle:
            return "rectangle";
        case Type::Trapezoid:
            return "trapezoid";
        case Type::Ellipse:
            return "ellipse";
        case Type::Triangle:
            return "triangle";
        case Type::Group:
            return "group";
        default:
            throw std::invalid_argument("Invalid type");
    }
}

std::string Converter::convertToString(const LineType& lineType) {
    switch (lineType) {
        case LineType::Solid:
            return "solid";
        case LineType::Dashed:
            return "dashed";
        case LineType::Dotted:
            return "dotted";
        default:
            throw std::invalid_argument("Invalid line type");
    }
}
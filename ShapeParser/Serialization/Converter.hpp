#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <string>
#include <unordered_map>
#include <algorithm>

#include "Data/ItemAttributes.hpp"

class QJsonArray;

class Converter {
    std::unordered_map<std::string, Type> typeMap;

public:
    Converter();
    Position convertToPosition(const std::vector<std::string>& values);
    Position convertToPosition(const std::string& str, const char delimiter);
    Type convertToType(const std::string& value);
    ID convertToID(const std::string& values);
    double convertToDimention(const std::string& value);
    long convertToColor(const std::string& color);
    LineType convertToLineType(const std::string& lineType);

    QJsonArray convertToArray(const Position& position);
    std::string convertToString(const Type& type);
    std::string convertToString(const LineType& lineType);
    

};

#endif
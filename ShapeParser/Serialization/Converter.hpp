#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <string>
#include <unordered_map>
#include <algorithm>

#include "Data/ItemAttributes.hpp"

class Converter {
    std::unordered_map<std::string, Type> typeMap;

public:
    Converter();
    Position convertToPosition(const std::vector<std::string>& values);
    Position convertToPosition(const std::string& str, const char delimiter);
    Type convertToType(const std::string& value);
    ID convertToID(const std::string& values);
    double convertToDimention(const std::string& value);
    //Dimentions convertToDimentions(const std::string& width, const std::string& height);
    long convertToColor(const std::string& color);
    LineType convertToLineType(const std::string& lineType);
    //LineDescriptor convertToLineDescriptor(const std::string& lineType, const std::string& lineWidth);
};

#endif
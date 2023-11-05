#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <string>
#include <unordered_map>
#include <algorithm>

#include "ItemAttributes.hpp"

class Converter {
    static std::unordered_map<std::string, Type> typeMap;

public:
    static Position convertToPosition(const std::vector<std::string>& values);
    static Position convertToPosition(const std::string& str, const char delimiter);
    static Type convertToType(const std::vector<std::string>& values);
    static Type convertToType(const std::string& value);
    static ID convertToID(const std::vector<std::string>& values);
    static ID convertToID(const std::string& values);
    static BoundingRect convertToBoundingRect(const std::string& width, const std::string& height);
    static long convertToColor(const std::string& color);
    static LineType convertToLineType(const std::string& lineType);
    static LineDescriptor convertToLineDescriptor(const std::string& lineType, const std::string& lineWidth);
};

#endif
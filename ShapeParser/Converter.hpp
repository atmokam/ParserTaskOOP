#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <string>
#include <unordered_map>

#include "ItemAttributes.hpp"

class Converter {
    static std::unordered_map<std::string, Type> typeMap;

public:
    static Position convertToPosition(const std::vector<std::string>& values);
    static Type convertToType(const std::vector<std::string>& values);
    static ID convertToID(const std::vector<std::string>& values);
    static BoundingRect convertToBoundingRect(const std::string& width, const std::string& height);
    static long convertToColor(const std::string& color);
};

#endif
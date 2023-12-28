#ifndef CONVERTER_HPP
#define CONVERTER_HPP
// converts between types

#include <string>
#include <unordered_map>
#include <algorithm>

#include "Data/Item/ItemAttributes.hpp"

namespace Renderer 
{
    enum class Type;
}

class QJsonArray;
class QJsonValue;

namespace Serialization
{
    class Converter 
    {
    public:
        Converter() = default;
        Data::Position convertToPosition(const std::vector<std::string>& values);
        Data::Position convertToPosition(const std::string& str, const char delimiter);
        Renderer::Type convertToType(const std::string& value);
        Data::ID convertToID(const std::string& values);
        double convertToDimention(const std::string& value);
        long convertToColor(const std::string& color);
        Data::LineType convertToLineType(const std::string& lineType);

        std::string convertToString(const Data::Position& position);
        std::string convertToString(const Renderer::Type type);
        std::string convertToString(const Data::LineType line);

    };
}
#endif
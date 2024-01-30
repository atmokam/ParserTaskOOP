#include "Converter.hpp"
#include "Application/Application.hpp"
#include "Renderer/Shape/ShapeLibrary.hpp"
#include <sstream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

namespace Serialization
{
    Data::Position Converter::convertToPosition(const std::vector<std::string>& values) 
    {
        std::vector<double> result;
        for (auto value : values) {
            result.push_back(std::stod(value));
        }
        return Data::Position{result};
    }

    Data::Position Converter::convertToPosition(const std::string& str, const char delimiter) 
    {
        std::vector<double> result;
        auto it = std::find(str.begin(), str.end(), delimiter);
        decltype(it) prev = str.begin();     
        while(it != str.end()){
            result.push_back(std::stod(std::string(prev, it)));
            prev = it + 1;
            it = std::find(prev, str.end(), delimiter);
        }

        result.push_back(std::stod(std::string(prev, it)));
        return Data::Position{result};
    }

    Renderer::Type Converter::convertToType(const std::string& value) 
    {
        Renderer::ShapeLibrary shapeLibrary;
        return shapeLibrary.getType(value); 
    }

    Data::ID Converter::convertToID(const std::string& value) 
    {
        return Data::ID{std::stoi(value)};
    }

    double Converter::convertToDimention(const std::string& value) 
    {
        return std::stod(value);
    }

    long Converter::convertToColor(const std::string& color) 
    {
        long converted = std::stol(color.substr(1), nullptr, 16);    
        return converted;
    }

    Data::LineType Converter::convertToLineType(const std::string& lineType) 
    {
        if (lineType == "solid") {
            return Data::LineType::Solid;
        } else if (lineType == "dashed") {
            return Data::LineType::Dashed;
        } else if (lineType == "dotted") {
            return Data::LineType::Dotted;
        } else {
            return Data::LineType::None;
        }
    }

    std::string Converter::convertToString(const Data::Position& position) 
    {
        std::stringstream result;
        for (auto value : position.getCoordinates()) {
            result << value << " ";
        }
        return result.str();
    }

    std::string Converter::convertToString(const Renderer::Type type)
    {
        Renderer::ShapeLibrary shapeLibrary;
        return shapeLibrary.getString(type);
    }

    std::string Converter::convertToString(const Data::LineType line)
    {
        switch(line)
        {
            case Data::LineType::Dashed:
                return "dashed";
            case Data::LineType::Dotted:
                return "dotted";
            case Data::LineType::Solid:
                return "solid";
            default:
                return "none";
        }
    }

}
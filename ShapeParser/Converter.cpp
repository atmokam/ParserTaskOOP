#include "Converter.hpp"


std::unordered_map<std::string, Type> Converter::typeMap = {
    {"line", Type::Line},
    {"rectangle", Type::Rectangle},
    {"trapezoid", Type::Trapezoid},
    {"ellipse", Type::Ellipse},
    {"triangle", Type::Triangle}
};


Position Converter::convertToPosition(const std::vector<std::string>& values) {
    std::vector<double> result;
    for (auto value : values) {
        result.push_back(std::stod(value));
    }
    return Position{result};
}

Type Converter::convertToType(const std::vector<std::string>& values) {
    auto it = typeMap.find(values[0]);
    return Type{it->second};
}

ID Converter::convertToID(const std::vector<std::string>& values) {
    return ID{std::stoi(values[0])};
}

BoundingRect Converter::convertToBoundingRect(const std::string& width, const std::string& height) { 
    return BoundingRect{std::stod(width), std::stod(height)};
}

Color Converter::convertToColor(const std::string& lColor, const std::string& fColor) {
    long line = std::stol(lColor.substr(1), nullptr, 16);
    long fill = std::stol(fColor.substr(1), nullptr, 16);
    return Color{line, fill};
}


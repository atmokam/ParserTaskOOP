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

Type Converter::convertToType(const std::vector<std::string>& values) {
    auto it = typeMap.find(values[0]);
    return Type{it->second};
}

Type Converter::convertToType(const std::string& value) {
    auto it = typeMap.find(value);
    return Type{it->second};
}

ID Converter::convertToID(const std::vector<std::string>& values) {
    return ID{std::stoi(values[0])};
}

ID Converter::convertToID(const std::string& value) {
    return ID{std::stoi(value)};
}

BoundingRect Converter::convertToBoundingRect(const std::string& width, const std::string& height) { 
    return BoundingRect{std::stod(width), std::stod(height)};
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

LineDescriptor Converter::convertToLineDescriptor(const std::string& lineType, const std::string& lineWidth) {
    return LineDescriptor{convertToLineType(lineType), std::stod(lineWidth)};
}

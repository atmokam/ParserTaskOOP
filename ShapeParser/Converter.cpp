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

Position Converter::convertToPosition(const std::string& str, const std::string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos) {
        token = str.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(str.substr (pos_start));
    Position pos = Converter::convertToPosition(res);
    return pos;
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

BoundingRect Converter::convertToBoundingRect(const std::string& width, const std::string& height) { 
    return BoundingRect{std::stod(width), std::stod(height)};
}

long Converter::convertToColor(const std::string& color) {
    long converted = std::stol(color.substr(1), nullptr, 16);    
    return converted;
}




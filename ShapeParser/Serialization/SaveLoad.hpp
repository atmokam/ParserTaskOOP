#ifndef SAVELOADSERIALIZER_HPP
#define SAVELOADSERIALIZER_HPP
// this class is responsible for saving the Document to device and loading from device

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>


#include "Data/ItemAttributes.hpp"

class IDocument;
class Slide;

class SaveLoad {
    void serialize(std::ostream& stream, const std::shared_ptr<Slide>& items);
    std::shared_ptr<IDocument> deserialize(std::ifstream& file);
public:
    void save(const std::shared_ptr<IDocument>& document, std::ostream& stream);
    std::shared_ptr<IDocument> load(const std::string& path);
};



inline std::ostream& operator<<(std::ostream& os, const LineDescriptor& line) {
    os << "line_style:";
    switch (line.type) {
        case LineType::Solid:
            os << "solid" << std::endl;
            break;
        case LineType::Dashed:
            os << "dashed" << std::endl;
            break;
        case LineType::Dotted:
            os << "dotted" << std::endl;
            break;
    }
    os << "line_width:" << line.width;
    return os;
}


inline std::ostream& operator<<(std::ostream& os, const ShapeType& shape) {
        os << "type:";
    switch (shape.type) {
        case Type::Rectangle:
            return os << "rectangle";
        case Type::Trapezoid:
            return os << "trapezoid";
        case Type::Ellipse:
            return os << "ellipse";
        case Type::Line:
            return os << "line";
        case Type::Triangle:
            return os << "triangle";
        default:
            return os;
    }
}

inline std::ostream& operator<<(std::ostream& os, const Position& position) {
    std::vector<double> coordinates = position.getCoordinates();
    os << "indices:";
    for (int i = 0; i < coordinates.size(); i++) {
        os << coordinates[i];
        if (i != coordinates.size() - 1) {
            os << " ";
        }
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const BoundingRect& boundingRect) {
    os << "width:" << boundingRect.width << std::endl;
    os << "height:" << boundingRect.height;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Color& color) {
    os << "line_color:#" << std::hex << color.hexLineColor << std::endl;
    os << "fill_color:#" << std::hex << color.hexFillColor;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Type& type) {
    switch (type) {
        case Type::Rectangle:
            return os << "rectangle";
        case Type::Trapezoid:
            return os << "trapezoid";
        case Type::Ellipse:
            return os << "ellipse";
        case Type::Line:
            return os << "line";
        case Type::Triangle:
            return os << "triangle";
        default:
            return os;
    }
}   

#endif



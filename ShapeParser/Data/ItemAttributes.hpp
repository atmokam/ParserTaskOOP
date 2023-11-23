#ifndef ITEMATTRIBUTES_HPP
#define ITEMATTRIBUTES_HPP

#include <vector>
#include <iostream>

class Position {
    std::vector<double> coordinates;
public:
    Position(std::vector<double> coordinates) : coordinates(coordinates) { }
    Position() = default;

    std::vector<double> getCoordinates() const { return coordinates; }
    void setCoordinates(std::vector<double> coordinates) { this->coordinates = coordinates; }
    friend std::ostream& operator<<(std::ostream& os, const Position& position);
};

enum class Type {
    Rectangle, Trapezoid, Ellipse, Line, Triangle
};

class ShapeType{
    Type type;

public:
    ShapeType(Type type) : type(type) { }
    Type getType() const { return type; }
    friend std::ostream& operator<<(std::ostream& os, const ShapeType& shape);
};

struct BoundingRect {
    double width;
    double height;
};

using ID = int;           

struct Color {
    long hexLineColor = 0;
    long hexFillColor = 0; // black by default
};

enum class LineType {
    Solid, Dashed, Dotted
};

struct LineDescriptor { // by default
    LineType type = LineType::Solid;
    double width = 1;
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


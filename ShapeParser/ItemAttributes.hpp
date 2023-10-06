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
    friend std::ostream& operator<<(std::ostream& os, const ShapeType& shape);
};

struct BoundingRect {
    double width;
    double height;
};

using ID = int; // 8 digit number

struct Color {
    long hexLineColor = 0;
    long hexFillColor = 0; // black by default
};


inline std::ostream& operator<<(std::ostream& os, const ShapeType& shape) {
    switch (shape.type) {
        case Type::Rectangle:
            return os << "Rectangle";
        case Type::Trapezoid:
            return os << "Trapezoid";
        case Type::Ellipse:
            return os << "Ellipse";
        case Type::Line:
            return os << "Line";
        case Type::Triangle:
            return os << "Triangle";
        default:
            return os;
    }
}

inline std::ostream& operator<<(std::ostream& os, const Position& position) {
    std::vector<double> coordinates = position.getCoordinates();
    os << " at indices ( ";
    for (int i = 0; i < coordinates.size(); i++) {
        os << coordinates[i];
        if (i != coordinates.size() - 1) {
            os << ", ";
        }
    }
    os << " )";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const BoundingRect& boundingRect) {
    os << "Width: " << boundingRect.width << ", Height: " << boundingRect.height;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Color& color) {
    os << "Line color: #" << std::hex << color.hexLineColor << ", Fill color: #" << std::hex << color.hexFillColor;
    return os;
}






#endif


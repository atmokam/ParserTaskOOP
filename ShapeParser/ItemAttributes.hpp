#ifndef ITEMATTRIBUTES_HPP
#define ITEMATTRIBUTES_HPP

#include <vector>

class Position {
    std::vector<double> coordinates;
public:
    Position(std::vector<double> coordinates) : coordinates(coordinates) { }
    Position() = default;

    std::vector<double> getCoordinates() const { return coordinates; }
    void setCoordinates(std::vector<double> coordinates) { this->coordinates = coordinates; }
};

enum class Type {
    Rectangle, Trapezoid, Ellipse, Line, Triangle
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

#endif


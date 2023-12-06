#ifndef ITEMATTRIBUTES_HPP
#define ITEMATTRIBUTES_HPP

#include <vector>
#include <iostream>

class Position 
{
    std::vector<double> coordinates;
public:
    Position(std::vector<double> coordinates) : coordinates(coordinates) { }
    Position() = default;

    std::vector<double> getCoordinates() const { return coordinates; }
    void setCoordinates(std::vector<double> coordinates) { this->coordinates = coordinates; }
    friend std::ostream& operator<<(std::ostream& os, const Position& position);
};

enum class Type 
{
    Rectangle, Trapezoid, Ellipse, Line, Triangle
};

class ShapeType
{
    Type type;

public:
    ShapeType(Type type) : type(type) { }
    Type getType() const { return type; }
    friend std::ostream& operator<<(std::ostream& os, const ShapeType& shape);
};

struct Dimentions 
{
    double width;
    double height;
};

using ID = int;           

struct Color 
{
    long hexLineColor = 0;
    long hexFillColor = 0; // black by default
};

enum class LineType 
{
    Solid, Dashed, Dotted
};

struct LineDescriptor 
{
    LineType type = LineType::Solid;
    double width = 1;
};


struct Attributes
{
    Color color;
    LineDescriptor line;
};

struct Geometry
{
    Position pos;
    Dimentions dimentions;
};


#endif


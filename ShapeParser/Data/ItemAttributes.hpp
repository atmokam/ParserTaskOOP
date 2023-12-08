#ifndef ITEMATTRIBUTES_HPP
#define ITEMATTRIBUTES_HPP

#include <vector>
#include <iostream>
#include <optional>

class Position 
{
    std::vector<double> coordinates = {0, 0};
public:
    Position(std::vector<double> coordinates) : coordinates(coordinates) { }
    Position() = default;

    std::vector<double> getCoordinates() const { return coordinates; }
    void setCoordinates(std::vector<double> coordinates) { this->coordinates = coordinates; }
    std::vector<double>::iterator begin() { return coordinates.begin(); }
    std::vector<double>::iterator end() { return coordinates.end(); }

    friend std::ostream& operator<<(std::ostream& os, const Position& position);
};

enum class LineType 
{
    Solid, Dashed, Dotted
};


class Attributes
{
    std::optional<long> hexFillColor = std::nullopt;
    std::optional<long> hexLineColor = std::nullopt;
    std::optional<LineType> lineType = std::nullopt;
    std::optional<double> lineWidth = std::nullopt;

public:
    Attributes() = default;
    Attributes(long hexFillColor, long hexLineColor, LineType lineType, double lineWidth) : 
        hexFillColor(hexFillColor), hexLineColor(hexLineColor), lineType(lineType), lineWidth(lineWidth) { }

    std::optional<long> getHexFillColor() const { return hexFillColor; }
    std::optional<long> getHexLineColor() const { return hexLineColor; }
    std::optional<LineType> getLineType() const { return lineType; }
    std::optional<double> getLineWidth() const { return lineWidth; }

    void setHexFillColor(long hexFillColor) { this->hexFillColor = hexFillColor; }
    void setHexLineColor(long hexLineColor) { this->hexLineColor = hexLineColor; }
    void setLineType(LineType lineType) { this->lineType = lineType; }
    void setLineWidth(double lineWidth) { this->lineWidth = lineWidth; }

    
};


class Geometry
{
    std::optional<Position> position = std::nullopt;
    std::optional<double> width = std::nullopt;
    std::optional<double> height = std::nullopt;

public:
    Geometry() = default;
    Geometry(Position position, double width, double height) : position(position), width(width), height(height) { }

    std::optional<Position>& getPosition() { return position; }
    std::optional<double>& getWidth() { return width; }
    std::optional<double>& getHeight() { return height; }

    void setPosition(Position position) { this->position = position; }
    void setWidth(double width) { this->width = width; }
    void setHeight(double height) { this->height = height; }

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

// struct Dimentions 
// {
//     double width;
//     double height;
// };

using ID = int;           

// struct Color 
// {
//     long hexLineColor = 0;
//     long hexFillColor = 0; // black by default
// };


// struct LineDescriptor 
// {
//     LineType type = LineType::Solid;
//     double width = 1;
// };




#endif


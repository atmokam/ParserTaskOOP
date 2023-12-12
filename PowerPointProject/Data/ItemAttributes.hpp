#ifndef ITEMATTRIBUTES_HPP
#define ITEMATTRIBUTES_HPP

#include <vector>
#include <optional>
#include <ostream>
#include "Renderer/ShapeLibrary.hpp"

class Position 
{
    std::vector<double> coordinates;
public:
    Position(std::vector<double> coordinates);
    Position() = default;

    std::vector<double> getCoordinates() const;
    void setCoordinates(std::vector<double> coordinates);
    std::vector<double>::iterator begin();
    std::vector<double>::iterator end();

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
    Attributes(long hexFillColor, long hexLineColor, LineType lineType, double lineWidth);
    std::optional<long> getHexFillColor() const;
    std::optional<long> getHexLineColor() const;
    std::optional<LineType> getLineType() const;
    std::optional<double> getLineWidth() const;

    void setHexFillColor(long hexFillColor);
    void setHexLineColor(long hexLineColor);
    void setLineType(LineType lineType);
    void setLineWidth(double lineWidth);

};


class Geometry
{
    std::optional<Position> position = std::nullopt;
    std::optional<double> width = std::nullopt;
    std::optional<double> height = std::nullopt;

public:
    Geometry() = default;
    Geometry(Position position, double width, double height);
    std::optional<Position> getPosition() const ;
    std::optional<double> getWidth() const ;
    std::optional<double> getHeight() const ;

    void setPosition(Position position) ;
    void setWidth(double width);
    void setHeight(double height);


};


class ShapeType
{
    Type type;

public:
    ShapeType(Type type) : type(type) { }
    Type getType() const { return type; }
    friend std::ostream& operator<<(std::ostream& os, const ShapeType& shape);
};


using ID = int;           

inline std::ostream& operator<<(std::ostream& os, const Position& position) {
    std::vector<double> coordinates = position.getCoordinates();
    for (int i = 0; i < coordinates.size(); i++) {
        os << coordinates[i];
        if (i != coordinates.size() - 1) {
            os << " ";
        }
    }
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
        case Type::Group:
            return os << "group";
        default:
            return os;
    }
}   

inline std::ostream& operator<<(std::ostream& os, const LineType& line) {
    switch (line) {
        case LineType::Solid:
            return os << "solid";
        case LineType::Dashed:
            return os << "dashed";
        case LineType::Dotted:
            return os << "dotted";
        default:
            return os;
    }
}



#endif


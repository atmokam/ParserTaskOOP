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
    std::optional<std::string> text = std::nullopt;

public:
    Attributes() = default;
    Attributes(long hexFillColor, long hexLineColor, LineType lineType, double lineWidth, std::string text);
    std::optional<long> getHexFillColor() const;
    std::optional<long> getHexLineColor() const;
    std::optional<LineType> getLineType() const;
    std::optional<double> getLineWidth() const;
    std::optional<std::string> getText() const;

    void setHexFillColor(long hexFillColor);
    void setHexLineColor(long hexLineColor);
    void setLineType(LineType lineType);
    void setLineWidth(double lineWidth);
    void setText(std::string text);

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

using ID = int;           



#endif


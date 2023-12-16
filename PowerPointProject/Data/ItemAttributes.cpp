#include "ItemAttributes.hpp"
#include <iostream>


Attributes::Attributes(long hexFillColor, long hexLineColor, LineType lineType, double lineWidth, std::string text) :
    hexFillColor(hexFillColor), hexLineColor(hexLineColor), lineType(lineType), lineWidth(lineWidth), text(text) { }

std::optional<long> Attributes::getHexFillColor() const { return hexFillColor; }

std::optional<long> Attributes::getHexLineColor() const { return hexLineColor; }

std::optional<LineType> Attributes::getLineType() const { return lineType; }

std::optional<double> Attributes::getLineWidth() const { return lineWidth; }

void Attributes::setHexFillColor(long hexFillColor) 
{
     this->hexFillColor = hexFillColor; 
}

void Attributes::setHexLineColor(long hexLineColor) 
{
     this->hexLineColor = hexLineColor; 
}

void Attributes::setLineType(LineType lineType) 
{
     this->lineType = lineType; }

void Attributes::setLineWidth(double lineWidth) 
{ 
    this->lineWidth = lineWidth; 
}

std::optional<std::string> Attributes::getText() const { return text; }

void Attributes::setText(std::string text) 
{
     this->text = text; 
}



Geometry::Geometry(Position position, double width, double height) :
    position(position), width(width), height(height) { }

std::optional<Position> Geometry::getPosition() const { return position; }

std::optional<double> Geometry::getWidth() const { return width; }

std::optional<double> Geometry::getHeight() const { return height; }

void Geometry::setPosition(Position position) 
{
     this->position = position; 
}

void Geometry::setWidth(double width) 
{
     this->width = width; 
}

void Geometry::setHeight(double height) 
{
     this->height = height; 
     
}


Position::Position(std::vector<double> coordinates) : coordinates(coordinates) { }

std::vector<double> Position::getCoordinates() const { return coordinates; }

void Position::setCoordinates(std::vector<double> coordinates) 
{
     this->coordinates = coordinates; 
}

std::vector<double>::iterator Position::begin() 
{
     return coordinates.begin(); 
}

std::vector<double>::iterator Position::end() 
{
     return coordinates.end(); 
}







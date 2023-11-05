#include "Item.hpp"


Item::Item(Type type, Position pos, BoundingRect boundingRect, Color color, ID id, LineDescriptor line) : type(type), pos(pos), boundingRect(boundingRect), color(color), id(id), line(line){
    
}

Position Item::getPosition() const {
    return pos;
}

Type Item::getType() const {
    return type;
}

BoundingRect Item::getBoundingRect() const {
    return boundingRect;
}

ID Item::getID() const {
    return id;
}

Color Item::getColor() const {
    return color;
}

LineDescriptor Item::getLineDescriptor() const {
    return line;
}

void Item::setPosition(Position pos) {
    this->pos = pos;
}

void Item::setType(Type type) {
    this->type = type;
}

void Item::setBoundingRect(BoundingRect boundingRect) {
    this->boundingRect = boundingRect;
}

void Item::setFillColor(long color) {
    this->color.hexFillColor = color;
}

void Item::setLineColor(long color) {
    this->color.hexLineColor = color;
}

void Item::setID(ID id) {
    this->id = id;
}

void Item::setLineDescriptorWidth(double width) {
    this->line.width = width;
}

void Item::setLineDescriptorStyle(LineType type) {
    this->line.type = type;
}

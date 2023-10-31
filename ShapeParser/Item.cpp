#include "Item.hpp"


Item::Item(Type type, Position pos, BoundingRect boundingRect, Color color, ID id) : type(type), pos(pos), boundingRect(boundingRect), color(color), id(id){
    
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

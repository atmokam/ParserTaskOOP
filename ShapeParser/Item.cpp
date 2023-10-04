#include "Item.hpp"

// TODO: implement

Item::Item(Type type, Position pos, BoundingRect boundingRect, Color color) : type(type), pos(pos), boundingRect(boundingRect), color(color) {
    id = generateID();
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

void Item::setColor(Color color) {
    this->color = color;
}


ID Item::generateID() {
    static ID id;
    return ++id;
}


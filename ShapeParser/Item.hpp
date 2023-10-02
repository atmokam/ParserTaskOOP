#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>

#include "ItemAttributes.hpp"

class Item {
    Position pos;
    Type type;
    BoundingRect boundingRect;
    ID id;
    Color color;

public:
    Item(Position pos, Type type, BoundingRect boundingRect, ID id, Color color) : pos(pos), type(type), boundingRect(boundingRect), id(id), color(color) { }

    Position getPosition() const { return pos; }
    Type getType() const { return type; }
    BoundingRect getBoundingRect() const { return boundingRect; }
    ID getID() const { return id; }
    Color getColor() const { return color; }

    void setPosition(Position pos) { this->pos = pos; }
    void setType(Type type) { this->type = type; }
    void setBoundingRect(BoundingRect boundingRect) { this->boundingRect = boundingRect; }
    void setColor(Color color) { this->color = color; }

};

#endif
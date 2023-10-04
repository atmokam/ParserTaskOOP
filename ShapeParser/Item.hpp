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

    ID generateID();

public:
    Item(Type type, Position pos, BoundingRect boundingRect, Color color);

    Position getPosition() const;
    Type getType() const;
    BoundingRect getBoundingRect() const;
    ID getID() const;
    Color getColor() const;

    void setPosition(Position pos);
    void setType(Type type);
    void setBoundingRect(BoundingRect boundingRect);
    void setColor(Color color);

};

#endif
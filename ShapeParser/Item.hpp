#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>
#include <memory>

#include "ItemAttributes.hpp"

class Item {
    Position pos;
    Type type;
    BoundingRect boundingRect;
    ID id;
    Color color;

public:

    Item() = default;   
    Item(Type type, Position pos, BoundingRect boundingRect, Color color, ID id);

    Position getPosition() const;
    Type getType() const;
    BoundingRect getBoundingRect() const;
    ID getID() const;
    Color getColor() const;

    void setID(ID id);
    void setPosition(Position pos);
    void setType(Type type);
    void setBoundingRect(BoundingRect boundingRect);
    void setFillColor(long color);
    void setLineColor(long color);

};

#endif
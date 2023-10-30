#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>
#include <memory>

#include "ItemAttributes.hpp"
#include "Slide.hpp"

class Slide;

class Item {
    Position pos;
    Type type;
    BoundingRect boundingRect;
    ID id;
    Color color;


public:
    ID generateID(std::shared_ptr<Slide> slide);
    Item() = default;   
    Item(Type type, Position pos, BoundingRect boundingRect, Color color);

    Position getPosition() const;
    Type getType() const;
    BoundingRect getBoundingRect() const;
    ID getID() const;
    Color getColor() const;

    void setPosition(Position pos);
    void setType(Type type);
    void setBoundingRect(BoundingRect boundingRect);
    void setFillColor(long color);
    void setLineColor(long color);

};

#endif
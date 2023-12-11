#ifndef ITEM_HPP
#define ITEM_HPP


#include "ItemAttributes.hpp"

class Item {
    Position pos;
    Type type;
    Dimentions dimentions;
    ID id;
    Color color;
    LineDescriptor line;

public:

    Item() = default;   
    Item(Type type, Position pos, Dimentions dimentions, Color color, ID id, LineDescriptor line);

    Position getPosition() const;
    Type getType() const;
    Dimentions getDimentions() const;
    ID getID() const;
    Color getColor() const;
    LineDescriptor getLineDescriptor() const;

    void setID(ID id);
    void setPosition(Position pos);
    void setType(Type type);
    void setDimentions(Dimentions dimentions);
    void setFillColor(long color);
    void setLineColor(long color);
    void setLineDescriptorWidth(double width);
    void setLineDescriptorStyle(LineType type);

};

#endif
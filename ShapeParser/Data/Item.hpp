#ifndef ITEM_HPP
#define ITEM_HPP


#include "ItemAttributes.hpp"
#include "IItem.hpp"

class Item : public IItem{
    Position pos;
    Type type;
    BoundingRect boundingRect;
    ID id;
    Color color;
    LineDescriptor line;

public:

    Item() = default;   
    Item(Type type, Position pos, BoundingRect boundingRect, Color color, ID id, LineDescriptor line);

    Position getPosition() const override;
    Type getType() const override;
    BoundingRect getBoundingRect() const override;
    ID getID() const override;
    Color getColor() const override;
    LineDescriptor getLineDescriptor() const override;

    void setID(ID id) override;
    void setPosition(Position pos) override;
    void setType(Type type) override;
    void setBoundingRect(BoundingRect boundingRect) override;
    void setFillColor(long color) override;
    void setLineColor(long color) override;
    void setLineDescriptorWidth(double width) override;
    void setLineDescriptorStyle(LineType type) override;

};

#endif
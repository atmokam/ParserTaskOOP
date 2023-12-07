#ifndef IITEM_HPP
#define IITEM_HPP

#include "ItemAttributes.hpp"

class IItem {
public:
    virtual Position getPosition() const = 0;
    virtual Type getType() const = 0;
    virtual BoundingRect getBoundingRect() const = 0;
    virtual ID getID() const = 0;
    virtual Color getColor() const = 0;
    virtual LineDescriptor getLineDescriptor() const = 0;

    virtual void setID(ID id) = 0;
    virtual void setPosition(Position pos) = 0;
    virtual void setType(Type type) = 0;
    virtual void setBoundingRect(BoundingRect boundingRect) = 0;
    virtual void setFillColor(long color) = 0;
    virtual void setLineColor(long color) = 0;
    virtual void setLineDescriptorWidth(double width) = 0;
    virtual void setLineDescriptorStyle(LineType type) = 0;

};

#endif

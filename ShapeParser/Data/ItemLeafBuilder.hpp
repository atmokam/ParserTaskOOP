#ifndef ITEMLEAFBUILDER_HPP
#define ITEMLEAFBUILDER_HPP

#include "ItemBase.hpp"

class ItemLeafBuilder {
    Type type;
    Geometry geometry;
    Attributes attributes;
public:
    ItemLeafBuilder() = default;
    ItemLeafBuilder& setType(Type type);
    ItemLeafBuilder& setGeometry(Geometry geometry);
    ItemLeafBuilder& setAttributes(Attributes attributes);

// for individual values
    ItemLeafBuilder& setPosition(Position pos);
    ItemLeafBuilder& setDimentionsWidth(double dimentions);
    ItemLeafBuilder& setDimentionsHeight(double dimentions);
    ItemLeafBuilder& setFillColor(long color);
    ItemLeafBuilder& setLineColor(long color);
    ItemLeafBuilder& setLineDescriptorWidth(double width);
    ItemLeafBuilder& setLineDescriptorStyle(LineType type);

    ItemLeaf build();
};

#endif
#include "ItemLeafBuilder.hpp"

ItemLeafBuilder& ItemLeafBuilder::setType(Type type) {
    this->type = type;
    return *this;
}

ItemLeafBuilder& ItemLeafBuilder::setGeometry(Geometry geometry) {
    this->geometry = geometry;
    return *this;
}

ItemLeafBuilder& ItemLeafBuilder::setAttributes(Attributes attributes) {
    this->attributes = attributes;
    return *this;
}

ItemLeafBuilder& ItemLeafBuilder::setPosition(Position pos) {
    geometry.pos = pos;
    return *this;
}

ItemLeafBuilder& ItemLeafBuilder::setDimentionsWidth(double dimentions) {
    geometry.dimentions.width = dimentions;
    return *this;
}

ItemLeafBuilder& ItemLeafBuilder::setDimentionsHeight(double dimentions) {
    geometry.dimentions.height = dimentions;
    return *this;
}

ItemLeafBuilder& ItemLeafBuilder::setFillColor(long color) {
    attributes.color.hexFillColor = color;
    return *this;
}

ItemLeafBuilder& ItemLeafBuilder::setLineColor(long color) {
    attributes.color.hexLineColor = color;
    return *this;
}

ItemLeafBuilder& ItemLeafBuilder::setLineDescriptorWidth(double width) {
    attributes.line.width = width;
    return *this;
}

ItemLeafBuilder& ItemLeafBuilder::setLineDescriptorStyle(LineType type) {
    attributes.line.type = type;
    return *this;
}

ItemLeaf ItemLeafBuilder::build() {
    return ItemLeaf(type, geometry, attributes);
}


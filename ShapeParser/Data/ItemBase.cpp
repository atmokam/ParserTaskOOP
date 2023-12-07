#include "ItemBase.hpp"

ID ItemBase::getID() const {
    return id;
}

void ItemBase::setID(ID id) {
    this->id = id;
}


// Leaf
ItemLeaf::ItemLeaf(Type type, Geometry geometry, Attributes attributes)
: type(type), geometry(geometry), attributes(attributes) {}

Type ItemLeaf::getType() const {
    return type;
}

Geometry ItemLeaf::getGeometry() const {
    return geometry;
}

Attributes ItemLeaf::getAttributes() const {
    return attributes;
}

void ItemLeaf::setType(Type type) {
    this->type = type;
}

void ItemLeaf::setGeometry(Geometry geometry) {
    this->geometry = geometry;
}

void ItemLeaf::setAttributes(Attributes attributes) {
    this->attributes = attributes;
}


// Group
ItemGroup::ItemGroup(std::unordered_map<ID, std::shared_ptr<ItemBase>>& items)
: items(items) {}

void ItemGroup::setItems(std::unordered_map<ID, std::shared_ptr<ItemBase>>& items) {
    this->items = items;
}

void ItemGroup::addItem(std::shared_ptr<ItemBase> item) {
    items.at(item->getID()) = item;
}

void ItemGroup::removeItem(ID id) {
    items.erase(id);
}

void ItemGroup::swapItems(ID idOfInitialItem, std::shared_ptr<ItemBase>& newItem) {
    items.at(idOfInitialItem) = newItem;
}

std::unordered_map<ID, std::shared_ptr<ItemBase>>::iterator ItemGroup::begin() {
    return items.begin();
}

std::unordered_map<ID, std::shared_ptr<ItemBase>>::const_iterator ItemGroup::cbegin() const {
    return items.cbegin();
}

std::unordered_map<ID, std::shared_ptr<ItemBase>>::iterator ItemGroup::end() {
    return items.end();
}

std::unordered_map<ID, std::shared_ptr<ItemBase>>::const_iterator ItemGroup::cend() const {
    return items.cend();
}

std::shared_ptr<ItemBase> ItemGroup::getItem(ID id) const {
    return items.at(id);
}


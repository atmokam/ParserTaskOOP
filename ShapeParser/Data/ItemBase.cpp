#include "ItemBase.hpp"


// Leaf
ItemLeaf::ItemLeaf(Type type, Geometry geometry, Attributes attributes)
: type(type), geometry(geometry), attributes(attributes) {}

ItemLeaf::ItemLeaf(std::shared_ptr<ItemLeaf> item)
: id(item->id), parent(item->parent), type(item->type), 
geometry(item->geometry), attributes(item->attributes) {}

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

std::shared_ptr<ItemGroup> ItemLeaf::getParent() const {
    return parent;
}

void ItemLeaf::setParent(std::shared_ptr<ItemGroup> parent) {
    this->parent = parent;
}

ID ItemLeaf::getID() const {
    return id;
}

void ItemLeaf::setID(ID id) {
    this->id = id;
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
    
    // actual implementation temporarily written in my copybook
    // this is just placeholder code
    if(items.find(id) == items.end()){
        return nullptr;
    }
    return items.at(id);


}

std::shared_ptr<ItemGroup> ItemGroup::getParent() const {
    return parent;
}

ID ItemGroup::getID() const {
    return id;
}

void ItemGroup::setID(ID id) {
    this->id = id;
}

void ItemGroup::setParent(std::shared_ptr<ItemGroup> parent) {
    this->parent = parent;
}


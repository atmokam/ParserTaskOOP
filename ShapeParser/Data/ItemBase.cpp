#include "ItemBase.hpp"
#include <algorithm>

// ItemBase

ItemBase::ItemBase() : type(), geometry(Geometry{}), attributes(Attributes{}), id(0) {}

ItemBase::ItemBase(Type type, Geometry& geometry, Attributes& attributes, ID id) 
: type(type), geometry(geometry), attributes(attributes), id(id) {}

// Leaf
ItemLeaf::ItemLeaf(Type type, Geometry& geometry, Attributes& attributes, ID id)
: ItemBase(type, geometry, attributes, id) {}

ItemLeaf::ItemLeaf(std::shared_ptr<ItemLeaf> item)
: ItemBase(item->type, item->geometry, item->attributes, item->id) {}


Type ItemLeaf::getType() const 
{
    return type;
}

Geometry ItemLeaf::getGeometry() const 
{
    return geometry;
}

Attributes ItemLeaf::getAttributes() const 
{
    return attributes;
}

void ItemLeaf::setType(Type type) 
{
    this->type = type;
}

void ItemLeaf::setDifferenceGeometry(Geometry& difference) 
{
    if(difference.getPosition().has_value()){
        std::transform(this->geometry.getPosition().value().begin(), 
        this->geometry.getPosition().value().end(),
        difference.getPosition().value().begin(), 
        this->geometry.getPosition().value().begin(), std::plus<double>());
    }
    
    if(difference.getWidth().has_value()){
        this->geometry.getWidth().value() += difference.getWidth().value();
    }
    if(difference.getHeight().has_value()){
        this->geometry.getHeight().value() += difference.getHeight().value();
    }
}

void ItemLeaf::setGeometry(Geometry& geometry) 
{
    this->geometry = geometry;
}

void ItemLeaf::setAttributes(Attributes& attributes)
{
    this->attributes = attributes;
}

std::shared_ptr<ItemGroup> ItemLeaf::getParent() const 
{
    return parent;
}

void ItemLeaf::setParent(std::shared_ptr<ItemGroup> parent) 
{
    this->parent = parent;
}

ID ItemLeaf::getID() const 
{
    return id;
}

void ItemLeaf::setID(ID id) 
{
    this->id = id;
}




// Group

ItemGroup::ItemGroup() : ItemBase(), items({}) {}

ItemGroup::ItemGroup(std::unordered_map<ID, std::shared_ptr<ItemBase>>& items, Geometry& geometry, 
Attributes& attributes, ID id)
: items(items), ItemBase(Type::Group, geometry, attributes, id) {}


Type ItemGroup::getType() const 
{
    return type;
}

void ItemGroup::setType(Type type) 
{
    this->type = type;
}

void ItemGroup::setItems(std::unordered_map<ID, std::shared_ptr<ItemBase>>& items) 
{
    this->items = items;
}

void ItemGroup::addItem(std::shared_ptr<ItemBase> item) 
{
    items[item->getID()] = item;
}

void ItemGroup::removeItem(ID id) 
{
    items.erase(id);
}

void ItemGroup::swapItems(ID idOfInitialItem, std::shared_ptr<ItemBase>& newItem) 
{
    items.at(idOfInitialItem) = newItem;
}

std::unordered_map<ID, std::shared_ptr<ItemBase>>::iterator ItemGroup::begin() 
{
    return items.begin();
}

std::unordered_map<ID, std::shared_ptr<ItemBase>>::const_iterator ItemGroup::cbegin() const 
{
    return items.cbegin();
}

std::unordered_map<ID, std::shared_ptr<ItemBase>>::iterator ItemGroup::end() 
{
    return items.end();
}

std::unordered_map<ID, std::shared_ptr<ItemBase>>::const_iterator ItemGroup::cend() const 
{
    return items.cend();
}

std::shared_ptr<ItemBase> ItemGroup::getItem(ID id) const 
{ 
    if(items.find(id) == items.end()){
        return nullptr;
    }
    return items.at(id);
}

Geometry ItemGroup::getGeometry() const 
{
    return geometry;
}

void ItemGroup::setDifferenceGeometry(Geometry& difference) 
{
    if(difference.getPosition().has_value()){
        std::transform(this->geometry.getPosition().value().begin(), this->geometry.getPosition().value().end(),
        difference.getPosition().value().begin(), this->geometry.getPosition().value().begin(), std::plus<double>());
    }
    
    if(difference.getWidth().has_value()){
        this->geometry.getWidth().value() += difference.getWidth().value();
    }
    if(difference.getHeight().has_value()){
        this->geometry.getHeight().value() += difference.getHeight().value();
    }


    for(auto& item : items)
    {
        item.second->setDifferenceGeometry(difference);

    }

}

void ItemGroup::setGeometry(Geometry& geometry) 
{
    std::vector<double> posDifferences;
    if(geometry.getPosition().has_value()) // check sizes
    {
        std::transform(this->geometry.getPosition().value().begin(), this->geometry.getPosition().value().end(),
        geometry.getPosition().value().begin(), std::back_inserter(posDifferences), std::minus<double>());
    }
    
    double widthDifference, heightDifference;
    if(geometry.getWidth().has_value())
    {
        widthDifference = this->geometry.getWidth().value() - geometry.getWidth().value();
    }

    if(geometry.getHeight().has_value())
    {
        heightDifference = this->geometry.getHeight().value() - geometry.getHeight().value();
    }

    Geometry difference(posDifferences, widthDifference, heightDifference);

    for(auto& item : items)
    {
        item.second->setDifferenceGeometry(difference);
    }
}


// handle when there are no values(it should get the default)
void ItemGroup::setAttributes(Attributes& attributes)
{
    for(auto& item : items)
    {
        item.second->setAttributes(attributes);

    }
}

Attributes ItemGroup::getAttributes() const 
{
    return Attributes{};
}


std::shared_ptr<ItemGroup> ItemGroup::getParent() const 
{
    return parent;
}

ID ItemGroup::getID() const 
{
    return id;
}

void ItemGroup::setID(ID id) 
{
    this->id = id;
}

void ItemGroup::setParent(std::shared_ptr<ItemGroup> parent) 
{
    this->parent = parent;
}


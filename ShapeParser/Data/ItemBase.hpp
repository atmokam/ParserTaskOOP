#ifndef ITEMBASE_HPP
#define ITEMBASE_HPP

#include <string>
#include <unordered_map>
#include <memory>

#include "ItemAttributes.hpp"

class ItemBase {
    ID id;
public:
    ID getID() const;
    void setID(ID id);
    virtual ~ItemBase() = default;
};

class ItemLeaf : public ItemBase {
    
    Type type;
    Geometry geometry;
    Attributes attributes;

public:
    ItemLeaf() = default;
    ItemLeaf(Type type, Geometry geometry, Attributes attributes);
    Type getType() const;
    Geometry getGeometry() const;
    Attributes getAttributes() const;
    
    // for when you have a geometry and attributes and you want to set them with those objects
    void setType(Type type);
    void setGeometry(Geometry geometry);
    void setAttributes(Attributes attributes);

};

class ItemGroup : public ItemBase {

    std::unordered_map<ID, std::shared_ptr<ItemBase>> items;
public:
    ItemGroup() = default;
    ItemGroup(std::unordered_map<ID, std::shared_ptr<ItemBase>>& items);
    
    void setItems(std::unordered_map<ID, std::shared_ptr<ItemBase>>& items);
    void addItem(std::shared_ptr<ItemBase> item);
    void removeItem(ID id);
    void swapItems(ID idOfInitialItem, std::shared_ptr<ItemBase>& newItem);
    std::shared_ptr<ItemBase> getItem(ID id) const;

    std::unordered_map<ID, std::shared_ptr<ItemBase>>::iterator begin();
    std::unordered_map<ID, std::shared_ptr<ItemBase>>::const_iterator cbegin() const;
    std::unordered_map<ID, std::shared_ptr<ItemBase>>::iterator end();
    std::unordered_map<ID, std::shared_ptr<ItemBase>>::const_iterator cend() const;


};



#endif

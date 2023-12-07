#ifndef ITEMBASE_HPP
#define ITEMBASE_HPP

#include <string>
#include <unordered_map>
#include <memory>

#include "ItemAttributes.hpp"



class ItemBase {
public:
    virtual ID getID() const = 0;
    virtual void setID(ID id) = 0;
    virtual ~ItemBase() = default;
    virtual std::shared_ptr<ItemGroup> getParent() const = 0;
    virtual void setParent(std::shared_ptr<ItemGroup> parent) = 0;
};

// in both leaf and group, we need to have a parent pointer, so that when we select
// an id from itemgroup, it checks whether it is has a parent, returns the the parent
// that's how selection operation works in Powerpoint
// I'm going to add "selected" in Controller


class ItemLeaf : public ItemBase {
    ID id;
    std::shared_ptr<ItemGroup> parent = nullptr;

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

    std::shared_ptr<ItemGroup> getParent() const override;
    void setParent(std::shared_ptr<ItemGroup> parent) override;
    ID getID() const override;
    void setID(ID id) override;

};

class ItemGroup : public ItemBase {
    ID id;
    std::shared_ptr<ItemGroup> parent = nullptr;

    std::unordered_map<ID, std::shared_ptr<ItemBase>> items;
public:
    ItemGroup() = default;
    ItemGroup(std::unordered_map<ID, std::shared_ptr<ItemBase>>& items);
    
    void setItems(std::unordered_map<ID, std::shared_ptr<ItemBase>>& items);
    void addItem(std::shared_ptr<ItemBase> item);
    void removeItem(ID id);
    void swapItems(ID idOfInitialItem, std::shared_ptr<ItemBase>& newItem);
    std::shared_ptr<ItemBase> getItem(ID id) const;
    std::shared_ptr<ItemGroup> getParent() const;

    std::unordered_map<ID, std::shared_ptr<ItemBase>>::iterator begin();
    std::unordered_map<ID, std::shared_ptr<ItemBase>>::const_iterator cbegin() const;
    std::unordered_map<ID, std::shared_ptr<ItemBase>>::iterator end();
    std::unordered_map<ID, std::shared_ptr<ItemBase>>::const_iterator cend() const;

    ID getID() const override;
    void setID(ID id) override;
    std::shared_ptr<ItemGroup> getParent() const override;
    void setParent(std::shared_ptr<ItemGroup> parent) override;


};


#endif

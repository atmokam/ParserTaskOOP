#ifndef ITEMBASE_HPP
#define ITEMBASE_HPP

#include <string>
#include <unordered_map>
#include <memory>

#include "ItemAttributes.hpp"


class ItemGroup;

class ItemBase {
public:
    virtual ID getID() const = 0;
    virtual void setID(ID id) = 0;
    virtual std::shared_ptr<ItemGroup> getParent() const = 0;
    virtual void setParent(std::shared_ptr<ItemGroup> parent) = 0;
    virtual Geometry getGeometry() const = 0;
    virtual void setAttributes(Attributes& attributes) = 0;
    virtual void setDifferenceGeometry(Geometry& difference) = 0;
    virtual void setGeometry(Geometry& geometry) = 0;
    virtual ~ItemBase() = default;
};

// in both leaf and group, we need to have a parent pointer, so that when we select
// an id from itemgroup, it checks whether it is has a parent, returns the the parent
// that's how selection operation works in Powerpoint (I think)


class ItemLeaf : public ItemBase {
    std::shared_ptr<ItemGroup> parent = nullptr;

    ID id;
    Type type;
    Geometry geometry;
    Attributes attributes;

public:
    ItemLeaf() = default;
    ItemLeaf(Type type, Geometry& geometry, Attributes& attributes, ID id);
    ItemLeaf(std::shared_ptr<ItemLeaf> item);
    Type getType() const;
    Attributes getAttributes() const;
    
    void setType(Type type);

    void setAttributes(Attributes& attributes) override;
    void setDifferenceGeometry(Geometry& difference) override;
    Geometry getGeometry() const override;
    void setGeometry(Geometry& geometry) override;
    std::shared_ptr<ItemGroup> getParent() const override;
    void setParent(std::shared_ptr<ItemGroup> parent) override;
    ID getID() const override;
    void setID(ID id) override;


};

class ItemGroup : public ItemBase {
    std::shared_ptr<ItemGroup> parent = nullptr;

    std::unordered_map<ID, std::shared_ptr<ItemBase>> items;

    ID id;
    Geometry geometry;
public:
    ItemGroup() = default;
    ItemGroup(std::unordered_map<ID, std::shared_ptr<ItemBase>>& items, Geometry& geometry);
    
    void setItems(std::unordered_map<ID, std::shared_ptr<ItemBase>>& items);
    void addItem(std::shared_ptr<ItemBase> item);
    void removeItem(ID id);
    void swapItems(ID idOfInitialItem, std::shared_ptr<ItemBase>& newItem);
    std::shared_ptr<ItemBase> getItem(ID id) const;

    std::unordered_map<ID, std::shared_ptr<ItemBase>>::iterator begin();
    std::unordered_map<ID, std::shared_ptr<ItemBase>>::const_iterator cbegin() const;
    std::unordered_map<ID, std::shared_ptr<ItemBase>>::iterator end();
    std::unordered_map<ID, std::shared_ptr<ItemBase>>::const_iterator cend() const;

    void setAttributes(Attributes& attributes) override;
    Geometry getGeometry() const override;
    void setDifferenceGeometry(Geometry& difference) override;
    void setGeometry(Geometry& geometry) override;
    ID getID() const override;
    void setID(ID id) override;
    std::shared_ptr<ItemGroup> getParent() const override;
    void setParent(std::shared_ptr<ItemGroup> parent) override;


};


#endif
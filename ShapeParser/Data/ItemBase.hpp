#ifndef ITEMBASE_HPP
#define ITEMBASE_HPP

#include <string>
#include <unordered_map>
#include <memory>

#include "ItemAttributes.hpp"


// in both ItemLeaf and ItemGroup, we need to have a parent pointer, so that when we select
// an id of ItemBase, it checks whether it is has a parent, and if it does, it selects the the parent
// that's how selection operation works in Powerpoint (as far as I have seen)

// I think a selection functionality might be needed 


class ItemGroup;

class ItemBase {  
protected:
    std::shared_ptr<ItemGroup> parent = nullptr;

    ID id;
    Type type;
    Geometry geometry;
    Attributes attributes;  
public:
    ItemBase();
    ItemBase(Type type, Geometry& geometry, Attributes& attributes, ID id) ;
    virtual Type getType() const = 0;
    virtual void setType(Type type) = 0;
    virtual ID getID() const = 0;
    virtual void setID(ID id) = 0;
    virtual std::shared_ptr<ItemGroup> getParent() const = 0;
    virtual void setParent(std::shared_ptr<ItemGroup> parent) = 0;
    virtual Geometry getGeometry() const = 0;
    virtual void setAttributes(Attributes& attributes) = 0;
    virtual Attributes getAttributes() const = 0;
    virtual void setDifferenceGeometry(Geometry& difference) = 0;
    virtual void setGeometry(Geometry& geometry) = 0;
    virtual ~ItemBase() = default;
}; 




class ItemLeaf : public ItemBase {

public:
    ItemLeaf() = default;
    ItemLeaf(Type type, Geometry& geometry, Attributes& attributes, ID id);
    ItemLeaf(std::shared_ptr<ItemLeaf> item);
    

    void setType(Type type) override;
    Type getType() const override;
    Attributes getAttributes() const override;
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

    std::unordered_map<ID, std::shared_ptr<ItemBase>> items;
public:
    ItemGroup();
    ItemGroup(std::unordered_map<ID, std::shared_ptr<ItemBase>>& items, Geometry& geometry, Attributes& attributes, ID id);
    
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
    Attributes getAttributes() const override;
    Geometry getGeometry() const override;
    void setDifferenceGeometry(Geometry& difference) override;
    void setGeometry(Geometry& geometry) override;
    ID getID() const override;
    void setID(ID id) override;
    std::shared_ptr<ItemGroup> getParent() const override;
    void setParent(std::shared_ptr<ItemGroup> parent) override;
    Type getType() const override;
    void setType(Type type) override;



};


#endif

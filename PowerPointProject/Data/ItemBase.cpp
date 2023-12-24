#include "ItemBase.hpp"
#include "Renderer/ShapeLibrary.hpp"
#include <algorithm>
#include <functional>
#include "Data/IVisitor.hpp"



// ItemBase

namespace Data
{    
    ItemBase::ItemBase() : type(), geometry(Geometry{}), attributes(Attributes{}), id() {}

    ItemBase::ItemBase(Renderer::Type type, Geometry& geometry, Attributes& attributes, ID id) 
    : type(type), geometry(geometry), attributes(attributes), id(id) {}

    // Leaf
    ItemLeaf::ItemLeaf(Renderer::Type type, Geometry& geometry, Attributes& attributes, ID id)
    : ItemBase(type, geometry, attributes, id) {}

    ItemLeaf::ItemLeaf(std::shared_ptr<ItemLeaf> item)
    : ItemBase(item->type, item->geometry, item->attributes, item->id) {}

    void ItemLeaf::accept(std::weak_ptr<IVisitor> visitor) 
    {
        visitor.lock()->visit(*this);
    }


    Renderer::Type ItemLeaf::getType() const 
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

    void ItemLeaf::setType(Renderer::Type type) 
    {
        this->type = type;
    }

    void ItemLeaf::setDifferenceGeometry(Geometry& difference) 
    {
        if(difference.getPosition().has_value())
        {
            std::transform(this->geometry.getPosition().value().begin(), 
            this->geometry.getPosition().value().end(),
            difference.getPosition().value().begin(), 
            this->geometry.getPosition().value().begin(), std::plus<double>());
        }
        
        if(difference.getWidth().has_value())
        {
            auto width = this->geometry.getWidth().value();
            width += difference.getWidth().value();
            this->geometry.setWidth(width);
        }
        if(difference.getHeight().has_value())
        {
            auto height = this->geometry.getHeight().value();
            height += difference.getHeight().value();
            this->geometry.setHeight(height);
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
    : items(items), ItemBase(Renderer::Type::Group, geometry, attributes, id) {}

    void ItemGroup::accept(std::weak_ptr<IVisitor> visitor) 
    {
        visitor.lock()->visit(*this);
    }

    Renderer::Type ItemGroup::getType() const 
    {
        return type;
    }

    void ItemGroup::setType(Renderer::Type type) 
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
        if(difference.getPosition().has_value())
        {
            std::transform(this->geometry.getPosition().value().begin(),
            this->geometry.getPosition().value().end(),
            difference.getPosition().value().begin(),
            this->geometry.getPosition().value().begin(), std::plus<double>());
        }
        
        if(difference.getWidth().has_value())
        {
            auto width = this->geometry.getWidth().value();
            width += difference.getWidth().value();
            this->geometry.setWidth(width);
        }
        if(difference.getHeight().has_value())
        {
            auto height = this->geometry.getHeight().value();
            height += difference.getHeight().value();
            this->geometry.setHeight(height);
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

    ID ItemGroup::getID() const 
    {
        return id;
    }

    void ItemGroup::setID(ID id) 
    {
        this->id = id;
    }
}
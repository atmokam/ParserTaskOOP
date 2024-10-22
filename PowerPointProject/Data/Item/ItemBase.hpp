#ifndef ITEMBASE_HPP
#define ITEMBASE_HPP

#include <string>
#include <unordered_map>
#include <memory>

#include "ItemAttributes.hpp"

namespace Renderer 
{
    enum class Type;
}

namespace Data
{
    class IItemVisitor;

    class ItemBase {  
    protected:

        ID id;
        Renderer::Type type;
        Geometry geometry;
        Attributes attributes;  
        
    public:
        ItemBase();
        ItemBase(Renderer::Type type, Geometry& geometry, Attributes& attributes, ID id) ;
        virtual Renderer::Type getType() const = 0;
        virtual void setType(Renderer::Type type) = 0;
        virtual ID getID() const = 0;
        virtual void setID(ID id) = 0;
        
        virtual Geometry getGeometry() const = 0;
        virtual void setAttributes(Attributes& attributes) = 0;
        virtual Attributes getAttributes() const = 0;
        virtual void setDifferenceGeometry(Geometry& difference) = 0;
        virtual void setGeometry(Geometry& geometry) = 0;
        virtual ~ItemBase() = default;

        virtual void accept(IItemVisitor& visitor) = 0;
    }; 





    class ItemLeaf : public ItemBase {
        
    public:
        ItemLeaf() = default;
        ItemLeaf(Renderer::Type type, Geometry& geometry, Attributes& attributes, ID id);
        ItemLeaf(std::shared_ptr<ItemLeaf> item);
        
        void setText(std::string text);
        std::string getText() const;
        void setType(Renderer::Type type) override;
        Renderer::Type getType() const override;
        Attributes getAttributes() const override;
        void setAttributes(Attributes& attributes) override;
        void setDifferenceGeometry(Geometry& difference) override;
        Geometry getGeometry() const override;
        void setGeometry(Geometry& geometry) override;
        
        ID getID() const override;
        void setID(ID id) override;

        void accept(IItemVisitor& visitor) override;


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
       
        Renderer::Type getType() const override;
        void setType(Renderer::Type type) override;

        void accept(IItemVisitor& visitor) override;

    };
}


#endif

#ifndef SLIDE_HPP
#define SLIDE_HPP

#include <string>
#include <memory>


#include "Item/ItemBase.hpp"

namespace Data
{
    class Slide {
        std::shared_ptr<ItemGroup> items;


    public:
        Slide();

        std::shared_ptr<ItemBase> getItem(ID id) const;

        void addItem(std::shared_ptr<ItemBase> item);
        void removeItem(ID id);
        void swapItems(ID idOfInitialItem, std::shared_ptr<ItemBase>& newItem);

        std::shared_ptr<ItemGroup> getTopItem() const;

        Slide(std::shared_ptr<Slide> slide);
    };
}

#endif

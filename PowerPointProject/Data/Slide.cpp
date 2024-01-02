#include <algorithm>
#include <unordered_map>
#include <iostream>
#include "Slide.hpp"
#include "Application/Application.hpp"

namespace Data
{
    Slide::Slide() : items(std::make_shared<ItemGroup>()) {}

    void Slide::addItem(std::shared_ptr<ItemBase> item) 
    {
        items->addItem(item);
    }

    std::shared_ptr<ItemBase> Slide::getItem(ID id) const  
    {  
        return items->getItem(id);
    }

    Slide::Slide(std::shared_ptr<Slide> slide) 
    { 
        items = slide->items;
    } 

    void Slide::removeItem(ID id) 
    {
        items->removeItem(id);
    }

    void Slide::swapItems(ID idOfInitialItem, std::shared_ptr<ItemBase>& newItem) 
    {
        items->swapItems(idOfInitialItem, newItem);  
    }

    std::shared_ptr<ItemGroup> Slide::getTopItem() const 
    {
        return items;
    }
}
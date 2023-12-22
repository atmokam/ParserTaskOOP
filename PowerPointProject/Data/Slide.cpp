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

    std::shared_ptr<ItemBase> Slide::getItem(int id) const  // only leaf for now
    {  
        auto item = items->getItem(id);
        auto controller = App::Application::getInstance()->getController();
        if(item == nullptr){
            controller->getOutputStream() << "Item with id " + std::to_string(id) + " does not exist" << std::endl;
            return nullptr;
        }
        return item;
    }

    Slide::Slide(std::shared_ptr<Slide> slide) 
    { 
        items = slide->items;
    } 

    void Slide::removeItem(int id) 
    {
        items->removeItem(id);
    }

    void Slide::swapItems(int idOfInitialItem, std::shared_ptr<ItemBase>& newItem) 
    {
        items->swapItems(idOfInitialItem, newItem);  
    }

    std::shared_ptr<ItemGroup> Slide::getTopItem() const 
    {
        return items;
    }
}
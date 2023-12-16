#ifndef SLIDE_HPP
#define SLIDE_HPP

#include <string>
#include <memory>


#include "ItemBase.hpp"

class Slide {
    std::shared_ptr<ItemGroup> items;


public:
    Slide();

    std::shared_ptr<ItemBase> getItem(int id) const;

    void addItem(std::shared_ptr<ItemBase> item);
    void removeItem(int id);
    void swapItems(int idOfInitialItem, std::shared_ptr<ItemBase>& newItem);

    std::shared_ptr<ItemGroup> getTopItem() const;

    Slide(std::shared_ptr<Slide> slide);
};


#endif

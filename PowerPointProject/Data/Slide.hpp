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

    // iterators
    std::unordered_map<ID, std::shared_ptr<ItemBase>>::iterator begin();
    std::unordered_map<ID, std::shared_ptr<ItemBase>>::const_iterator cbegin() const;

    std::unordered_map<ID, std::shared_ptr<ItemBase>>::iterator end();
    std::unordered_map<ID, std::shared_ptr<ItemBase>>::const_iterator cend() const;


    Slide(std::shared_ptr<Slide> slide);
};


#endif

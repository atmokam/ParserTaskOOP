#ifndef SLIDE_HPP
#define SLIDE_HPP

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <unordered_map>


#include "Item.hpp"

class Item;

class Slide {
    std::unordered_map<int, std::shared_ptr<Item>> items;
    size_t maximumID = 0;
public:
    Slide() = default;

    std::unordered_map<int, std::shared_ptr<Item>> getItems() const;
    std::shared_ptr<Item> getItem(int id) const;
    size_t getMaximumID() const ;
    void setMaximumID(size_t id);
    void incrementMaximumID();
    
    void addItem(std::shared_ptr<Item> item);
    void removeItem(int id);

    Slide(std::shared_ptr<Slide> slide);
};


#endif
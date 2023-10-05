#ifndef SLIDE_HPP
#define SLIDE_HPP

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <unordered_map>


#include "Item.hpp"

class Slide {
    std::unordered_map<int, std::shared_ptr<Item>> items;
public:
    Slide() = default;

    std::unordered_map<int, std::shared_ptr<Item>> getItems() const;
    
    void addItem(std::shared_ptr<Item> item);
    void removeItem(int id);
};


#endif
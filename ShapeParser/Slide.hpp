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
    size_t maximumID = 0;



public:
    Slide() = default;

    ID generateID();
    std::unordered_map<int, std::shared_ptr<Item>> getItems() const; //
    std::shared_ptr<Item> getItem(int id) const;
    size_t getMaximumID() const ;
    void setMaximumID(size_t id);
    void incrementMaximumID();
    
    void addItem(std::shared_ptr<Item> item);
    void removeItem(int id);

    std::unordered_map<int, std::shared_ptr<Item>>::iterator begin();
    std::unordered_map<int, std::shared_ptr<Item>>::const_iterator cbegin() const;

    std::unordered_map<int, std::shared_ptr<Item>>::iterator end();
    std::unordered_map<int, std::shared_ptr<Item>>::const_iterator cend() const;


    Slide(std::shared_ptr<Slide> slide);
};


#endif
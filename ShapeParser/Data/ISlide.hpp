#ifndef ISLIDE_HPP
#define ISLIDE_HPP

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

#include "Item.hpp"

using SlideContainer = std::unordered_map<int, std::shared_ptr<Item>>;

class ISlide {
public:
    virtual ID generateID() = 0;
    virtual std::shared_ptr<Item> getItem(int id) const = 0;
    virtual size_t getMaximumID() const  = 0;
    virtual void setMaximumID(size_t id) = 0;
    virtual void incrementMaximumID() = 0;
    
    virtual void addItem(std::shared_ptr<Item> item) = 0;
    virtual void removeItem(int id) = 0;
    virtual void swapItems(int idOfInitialItem, std::shared_ptr<Item>& newItem) = 0;

    virtual SlideContainer::iterator begin() = 0;
    virtual SlideContainer::const_iterator cbegin() const = 0;

    virtual SlideContainer::iterator end() = 0;
    virtual SlideContainer::const_iterator cend() const = 0;


};


#endif
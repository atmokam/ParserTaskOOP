#ifndef SLIDE_HPP
#define SLIDE_HPP

#include <string>
#include <memory>


#include "ISlide.hpp"

class Item;

class Slide : public ISlide {
    SlideContainer items;
    size_t maximumID = 0;
    SlideContainer getItems() const; 

public:
    Slide() = default;

    // generateID is static method, what will happen if I override it and always return 1?
    ID generateID() override;

    // [TK] those function doesn't look like Interface methoids, why are they here?
    std::shared_ptr<Item> getItem(int id) const override;
    size_t getMaximumID() const  override;
    void setMaximumID(size_t id) override;
    void incrementMaximumID() override;
    
    void addItem(std::shared_ptr<Item> item) override;
    void removeItem(int id) override;
    void swapItems(int idOfInitialItem, std::shared_ptr<Item>& newItem) override;

    SlideContainer::iterator begin() override;
    SlideContainer::const_iterator cbegin() const override;

    SlideContainer::iterator end() override;
    SlideContainer::const_iterator cend() const override;


    Slide(std::shared_ptr<Slide> slide);
};


#endif

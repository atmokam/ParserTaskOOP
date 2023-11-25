#include "Slide.hpp"


SlideContainer Slide::getItems() const {
    return items;
}

void Slide::addItem(std::shared_ptr<Item> item) {
    items[item->getID()] = item;
}

void Slide::removeItem(int id) {
    items.erase(id);
}

std::shared_ptr<Item> Slide::getItem(int id) const {
    return items.at(id);
}

Slide::Slide(std::shared_ptr<Slide> slide) { 
    items = slide->getItems();
    maximumID = slide->getMaximumID();
}

void Slide::setMaximumID(size_t id) {
    maximumID = id;
}

size_t Slide::getMaximumID() const {
    return maximumID;
}

// size_t Slide::getSlideNumber() const {
//     return slideNumber;
// }

// void Slide::setSlideNumber(size_t number) {
//     slideNumber = number;
// }

void Slide::incrementMaximumID() {
    ++maximumID;
}

ID Slide::generateID() {
    incrementMaximumID();
    return getMaximumID();
}

void Slide::swapItems(int idOfInitialItem, std::shared_ptr<Item>& newItem) {
    std::swap(items[idOfInitialItem], newItem);
}

SlideContainer::iterator Slide::begin() {
    return items.begin();
}

SlideContainer::const_iterator Slide::cbegin() const {
    return items.cbegin();
}

SlideContainer::iterator Slide::end() {
    return items.end();
}

SlideContainer::const_iterator Slide::cend() const {
    return items.cend();
}

#include "Slide.hpp"


SlideContainer Slide::getItems() const {
    return items;
}

void Slide::addItem(std::shared_ptr<Item> item) {
    items[item->getID()] = item;
    std::cout << "Item with id " + std::to_string(item->getID()) + " added" << std::endl;
}

void Slide::removeItem(int id) {
    items.erase(id);
}

std::shared_ptr<Item> Slide::getItem(int id) const {
    if(items.find(id) == items.end()){
        std::cout << "Item with id " + std::to_string(id) + " does not exist" << std::endl;
        return nullptr;
    }
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

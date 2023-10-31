#include "Slide.hpp"


std::unordered_map<int, std::shared_ptr<Item>> Slide::getItems() const {
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

void Slide::incrementMaximumID() {
    ++maximumID;
}

ID Slide::generateID() {
    incrementMaximumID();
    return getMaximumID();
}


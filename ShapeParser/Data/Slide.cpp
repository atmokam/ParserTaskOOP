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

void Slide::swapItems(int idOfInitialItem, std::shared_ptr<Item>& newItem) {
    std::swap(items[idOfInitialItem], newItem);
}

std::unordered_map<int, std::shared_ptr<Item>>::iterator Slide::begin() {
    return items.begin();
}

std::unordered_map<int, std::shared_ptr<Item>>::const_iterator Slide::cbegin() const {
    return items.cbegin();
}

std::unordered_map<int, std::shared_ptr<Item>>::iterator Slide::end() {
    return items.end();
}

std::unordered_map<int, std::shared_ptr<Item>>::const_iterator Slide::cend() const {
    return items.cend();
}

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





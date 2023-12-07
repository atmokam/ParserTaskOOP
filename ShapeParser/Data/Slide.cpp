#include <algorithm>
#include <unordered_map>
#include "Slide.hpp"
#include "Item.hpp"

void Slide::addItem(std::shared_ptr<ItemBase> item) {
    items.addItem(item);
}

std::shared_ptr<ItemBase> Slide::getItem(int id) const {  // only returns leaf for now
auto item = items.getItem(id);
    if(item == nullptr){
        std::cout << "Item with id " + std::to_string(id) + " does not exist" << std::endl;
        return nullptr;
    }
    return item;
}

Slide::Slide(std::shared_ptr<Slide> slide) { 
    items = slide->items;
} ////

void Slide::removeItem(int id) {
    items.removeItem(id);
}

void Slide::swapItems(int idOfInitialItem, std::shared_ptr<ItemBase>& newItem) {
    items.swapItems(idOfInitialItem, newItem);  
}


std::unordered_map<ID, std::shared_ptr<ItemBase>>::iterator Slide::begin() {
    return items.begin();
}

std::unordered_map<ID, std::shared_ptr<ItemBase>>::const_iterator Slide::cbegin() const {
    return items.cbegin();
}

std::unordered_map<ID, std::shared_ptr<ItemBase>>::iterator Slide::end() {
    return items.end();
}

std::unordered_map<ID, std::shared_ptr<ItemBase>>::const_iterator Slide::cend() const {
    return items.cend();
}

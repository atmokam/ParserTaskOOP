#include "Director/Actions.hpp"



AddItem::AddItem(const std::shared_ptr<Item>& item, size_t slideNumber) : item(item), slideNumber(slideNumber) {}

std::shared_ptr<IAction> AddItem::execute(IDocument& document) {
    document.getSlide(slideNumber)->addItem(item);
    return std::make_shared<RemoveItem>(item, slideNumber);
    
}

AddSlide::AddSlide(const std::shared_ptr<Slide>& slide, size_t slideNumber) : slide(slide), slideNumber(slideNumber) {}

std::shared_ptr<IAction> AddSlide::execute(IDocument& document) {
    document.addSlide(slide, slideNumber);
    return std::make_shared<RemoveSlide>(slide, slideNumber);
}

RemoveItem::RemoveItem(const std::shared_ptr<Item>& item, size_t slideNumber) : item(item), slideNumber(slideNumber) {}

std::shared_ptr<IAction> RemoveItem::execute(IDocument& document) {
    document.getSlide(slideNumber)->removeItem(item->getID());
    return std::make_shared<AddItem>(item, slideNumber);
}

RemoveSlide::RemoveSlide(const std::shared_ptr<Slide>& slide, size_t slideNumber) : slide(slide), slideNumber(slideNumber) {}

std::shared_ptr<IAction> RemoveSlide::execute(IDocument& document) {
    document.removeSlide(slide);
    return std::make_shared<AddSlide>(slide, slideNumber);
}

ChangeItem::ChangeItem(const std::shared_ptr<Item>& item, size_t slideNumber) : item(item), slideNumber(slideNumber) {}   

std::shared_ptr<IAction> ChangeItem::execute(IDocument& document) {
    std::shared_ptr<Item> oldItem = document.getSlide(slideNumber)->getItem(item->getID()); // item has the same id number
    document.getSlide(slideNumber)->swapItems(item->getID(), item);
    return std::make_shared<ChangeItem>(oldItem, slideNumber);
}


#include "Actions.hpp"
#include "Data/Document.hpp"
#include "Include/IDocument.hpp"
#include "Serialization/Converter.hpp"
#include "Serialization/SaveLoad.hpp"
#include "Data/Slide.hpp"
#include "Data/ItemBase.hpp"



AddItem::AddItem(const std::shared_ptr<ItemBase>& item, size_t slideNumber) : item(item), slideNumber(slideNumber) {}

std::shared_ptr<IAction> AddItem::execute(std::shared_ptr<IDocument>& document) 
{
    document->getSlide(slideNumber)->addItem(item);  
    return std::make_shared<RemoveItem>(item, slideNumber);
    
}

AddSlide::AddSlide(const std::shared_ptr<Slide>& slide, size_t slideNumber) : slide(slide), slideNumber(slideNumber) {}

std::shared_ptr<IAction> AddSlide::execute(std::shared_ptr<IDocument>& document) 
{
    document->addSlide(slide, slideNumber);
    return std::make_shared<RemoveSlide>(slide, slideNumber);
}

RemoveItem::RemoveItem(const std::shared_ptr<ItemBase>& item, size_t slideNumber) : item(item), slideNumber(slideNumber) {}

std::shared_ptr<IAction> RemoveItem::execute(std::shared_ptr<IDocument>& document) 
{
    document->getSlide(slideNumber)->removeItem(item->getID());
    return std::make_shared<AddItem>(item, slideNumber);
}

RemoveSlide::RemoveSlide(const std::shared_ptr<Slide>& slide, size_t slideNumber) : slide(slide), slideNumber(slideNumber) {}

std::shared_ptr<IAction> RemoveSlide::execute(std::shared_ptr<IDocument>& document) {
    document->removeSlide(slideNumber);
    return std::make_shared<AddSlide>(slide, slideNumber);
}

ChangeItem::ChangeItem(const std::shared_ptr<ItemBase>& item, size_t slideNumber) : item(item), slideNumber(slideNumber) {}   

std::shared_ptr<IAction> ChangeItem::execute(std::shared_ptr<IDocument>& document) {
    std::shared_ptr<ItemBase> oldItem = document->getSlide(slideNumber)->getItem(item->getID()); // item has the same id number
    document->getSlide(slideNumber)->swapItems(item->getID(), item);
    return std::make_shared<ChangeItem>(oldItem, slideNumber);
}


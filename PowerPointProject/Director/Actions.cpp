#include "Actions.hpp"
#include "Data/Document.hpp"
#include "Include/IDocument.hpp"
#include "Serialization/Converter.hpp"
#include "Serialization/SaveLoad.hpp"
#include "Data/Slide.hpp"
#include "Data/ItemBase.hpp"


namespace Director
{

    AddItem::AddItem(const std::shared_ptr<Data::ItemBase>& item, size_t slideNumber) : item(item), slideNumber(slideNumber) {}

    std::shared_ptr<IAction> AddItem::execute(std::shared_ptr<Data::IDocument>& document) 
    {
        document->getSlide(slideNumber)->addItem(item);  
        return std::make_shared<RemoveItem>(item, slideNumber);
        
    }

    AddSlide::AddSlide(const std::shared_ptr<Data::Slide>& slide, size_t slideNumber) : slide(slide), slideNumber(slideNumber) {}

    std::shared_ptr<IAction> AddSlide::execute(std::shared_ptr<Data::IDocument>& document) 
    {
        document->addSlide(slide, slideNumber);
        return std::make_shared<RemoveSlide>(slide, slideNumber);
    }

    RemoveItem::RemoveItem(const std::shared_ptr<Data::ItemBase>& item, size_t slideNumber) : item(item), slideNumber(slideNumber) {}

    std::shared_ptr<IAction> RemoveItem::execute(std::shared_ptr<Data::IDocument>& document) 
    {
        document->getSlide(slideNumber)->removeItem(item->getID());
        return std::make_shared<AddItem>(item, slideNumber);
    }

    RemoveSlide::RemoveSlide(const std::shared_ptr<Data::Slide>& slide, size_t slideNumber) : slide(slide), slideNumber(slideNumber) {}

    std::shared_ptr<IAction> RemoveSlide::execute(std::shared_ptr<Data::IDocument>& document) {
        document->removeSlide(slideNumber);
        return std::make_shared<AddSlide>(slide, slideNumber);
    }

    ChangeAttributes::ChangeAttributes(Data::Attributes& newAttributes, Data::ID itemId, size_t slideNumber) : newAttributes(newAttributes), itemId(itemId), slideNumber(slideNumber) {}
   
    
    std::shared_ptr<IAction> ChangeAttributes::execute(std::shared_ptr<Data::IDocument>& document)
    {
        std::shared_ptr<Data::ItemBase> item = document->getSlide(slideNumber)->getItem(itemId);
        Data::Attributes oldAttributes = item->getAttributes();
        item->setAttributes(newAttributes);
        return std::make_shared<ChangeAttributes>(oldAttributes, itemId, slideNumber);
    }


    ChangeGeometry::ChangeGeometry(Data::Geometry& newGeometry, Data::ID itemId, size_t slideNumber) : newGeometry(newGeometry), itemId(itemId), slideNumber(slideNumber) {}
    std::shared_ptr<IAction> ChangeGeometry::execute(std::shared_ptr<Data::IDocument>& document) 
    {
        std::shared_ptr<Data::ItemBase> item = document->getSlide(slideNumber)->getItem(itemId);
        Data::Geometry oldGeometry = item->getGeometry();
        item->setGeometry(newGeometry);
        return std::make_shared<ChangeGeometry>(oldGeometry, itemId, slideNumber);
    }

    // ChangeItem::ChangeItem(const std::shared_ptr<Data::ItemBase>& item, size_t slideNumber) : item(item), slideNumber(slideNumber) {}   

    // std::shared_ptr<IAction> ChangeItem::execute(std::shared_ptr<Data::IDocument>& document) {
    //     std::shared_ptr<Data::ItemBase> oldItem = document->getSlide(slideNumber)->getItem(item->getID()); // item has the same id number
    //     document->getSlide(slideNumber)->swapItems(item->getID(), item);
    //     return std::make_shared<ChangeItem>(oldItem, slideNumber);
    // }

}
#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <string>
#include <memory>

#include "Include/IDocument.hpp"
#include "IAction.hpp"
#include "Data/ItemAttributes.hpp"

namespace Data
{
    class ItemBase;
    class Slide;
}



namespace Director
{
    class AddItem : public IAction {
        std::shared_ptr<Data::ItemBase> item;
        size_t slideNumber;
    public:
        AddItem(const std::shared_ptr<Data::ItemBase>& item, size_t slideNumber);
        std::shared_ptr<IAction> execute(std::shared_ptr<Data::IDocument>& document) override; 
    };

    class AddSlide : public IAction {
        std::shared_ptr<Data::Slide> slide;
        size_t slideNumber;
    public:
        AddSlide(const std::shared_ptr<Data::Slide>& slide, size_t slideNumber);
        std::shared_ptr<IAction> execute(std::shared_ptr<Data::IDocument>& document) override; 
    };

    class RemoveItem : public IAction {
        std::shared_ptr<Data::ItemBase> item;
        size_t slideNumber;
    public:
        RemoveItem(const std::shared_ptr<Data::ItemBase>& item, size_t slideNumber);
        std::shared_ptr<IAction> execute(std::shared_ptr<Data::IDocument>& document) override; 
    };

    class RemoveSlide : public IAction {
        std::shared_ptr<Data::Slide> slide;
        size_t slideNumber;
    public:
        RemoveSlide(const std::shared_ptr<Data::Slide>& slide, size_t slideNumber);
        std::shared_ptr<IAction> execute(std::shared_ptr<Data::IDocument>& document) override; 
    };

    class ChangeAttributes : public IAction {
        Data::Attributes newAttributes;
        Data::ID itemId;
        size_t slideNumber;
    public:
        ChangeAttributes(Data::Attributes& newAttributes, Data::ID itemId, size_t slideNumber);
        std::shared_ptr<IAction> execute(std::shared_ptr<Data::IDocument>& document) override; 
    };

    class ChangeGeometry : public IAction {
        Data::Geometry newGeometry;
        Data::ID itemId;
        size_t slideNumber;
    public:
        ChangeGeometry(Data::Geometry& newGeometry, Data::ID itemId, size_t slideNumber);
        std::shared_ptr<IAction> execute(std::shared_ptr<Data::IDocument>& document) override; 
    };
}

#endif
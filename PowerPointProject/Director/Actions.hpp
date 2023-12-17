#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <string>
#include <memory>

#include "Include/IDocument.hpp"
#include "IAction.hpp"

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

    class ChangeItem : public IAction {
        std::shared_ptr<Data::ItemBase> item;
        size_t slideNumber;
    public:
        ChangeItem(const std::shared_ptr<Data::ItemBase>& item, size_t slideNumber);
        std::shared_ptr<IAction> execute(std::shared_ptr<Data::IDocument>& document) override; 
    };
}

#endif
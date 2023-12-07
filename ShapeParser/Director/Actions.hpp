#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <string>
#include <memory>


class Slide; // forward declared as non-interfaces for now, will be changed to interfaces later
class Item;

#include "IAction.hpp"
class ItemBase;


class AddItem : public IAction {
    std::shared_ptr<ItemBase> item;
    size_t slideNumber;
public:
    AddItem(const std::shared_ptr<ItemBase>& item, size_t slideNumber);
    std::shared_ptr<IAction> execute(std::shared_ptr<IDocument>& document) override; 
};

class AddSlide : public IAction {
    std::shared_ptr<Slide> slide;
    size_t slideNumber;
public:
    AddSlide(const std::shared_ptr<Slide>& slide, size_t slideNumber);
    std::shared_ptr<IAction> execute(std::shared_ptr<IDocument>& document) override; 
};

class RemoveItem : public IAction {
    std::shared_ptr<ItemBase> item;
    size_t slideNumber;
public:
    RemoveItem(const std::shared_ptr<ItemBase>& item, size_t slideNumber);
    std::shared_ptr<IAction> execute(std::shared_ptr<IDocument>& document) override; 
};

class RemoveSlide : public IAction {
    std::shared_ptr<Slide> slide;
    size_t slideNumber;
public:
    RemoveSlide(const std::shared_ptr<Slide>& slide, size_t slideNumber);
    std::shared_ptr<IAction> execute(std::shared_ptr<IDocument>& document) override; 
};

class ChangeItem : public IAction {
    std::shared_ptr<ItemBase> item;
    size_t slideNumber;
public:
    ChangeItem(const std::shared_ptr<ItemBase>& item, size_t slideNumber);
    std::shared_ptr<IAction> execute(std::shared_ptr<IDocument>& document) override; 
};


#endif
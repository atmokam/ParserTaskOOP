#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <string>
#include <iostream>
#include <memory>

#include "Data/Document.hpp"
#include "Data/Item.hpp"
#include "Serialization/Converter.hpp"
#include "Serialization/SaveLoad.hpp"
#include "IAction.hpp"
#include "Renderer/IRenderer.hpp"
#include "Include/IDocument.hpp"


class AddItem : public IAction {
    std::shared_ptr<Item> item;
    size_t slideNumber;
public:
    AddItem(const std::shared_ptr<Item>& item, size_t slideNumber);
    std::shared_ptr<IAction> execute(IDocument& document) override; // current slide index is in item
};

class AddSlide : public IAction {
    std::shared_ptr<Slide> slide;
    size_t slideNumber;
public:
    AddSlide(const std::shared_ptr<Slide>& slide, size_t slideNumber);
    std::shared_ptr<IAction> execute(IDocument& document) override; 
};

class RemoveItem : public IAction {
    std::shared_ptr<Item> item;
    size_t slideNumber;
public:
    RemoveItem(const std::shared_ptr<Item>& item, size_t slideNumber);
    std::shared_ptr<IAction> execute(IDocument& document) override; 
};

class RemoveSlide : public IAction {
    std::shared_ptr<Slide> slide;
    size_t slideNumber;
public:
    RemoveSlide(const std::shared_ptr<Slide>& slide, size_t slideNumber);
    std::shared_ptr<IAction> execute(IDocument& document) override; 
};

class ChangeItem : public IAction {
    std::shared_ptr<Item> item;
    size_t slideNumber;
public:
    ChangeItem(const std::shared_ptr<Item>& item, size_t slideNumber);
    std::shared_ptr<IAction> execute(IDocument& document) override; 
};


#endif
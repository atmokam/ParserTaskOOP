#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <fstream>

#include "Data/Document.hpp"
#include "Data/Item.hpp"
#include "Data/Slide.hpp"
#include "Serialization/Converter.hpp"
#include "Serialization/SaveLoad.hpp"
#include "IAction.hpp"
#include "Renderer/IRenderer.hpp"


class AddItem : public IAction {
    std::shared_ptr<Item> item;
    size_t slideNumber;
public:
    AddItem(const std::shared_ptr<Item>& item, size_t slideNumber);
    std::shared_ptr<IAction> execute(std::shared_ptr<Document>& document) override; // current slide index is in item
};

class AddSlide : public IAction {
    std::shared_ptr<Slide> slide;
    size_t slideNumber;
public:
    AddSlide(const std::shared_ptr<Slide>& slide, size_t slideNumber);
    std::shared_ptr<IAction> execute(std::shared_ptr<Document>& document) override; 
};

class RemoveItem : public IAction {
    std::shared_ptr<Item> item;
    size_t slideNumber;
public:
    RemoveItem(const std::shared_ptr<Item>& item, size_t slideNumber);
    std::shared_ptr<IAction> execute(std::shared_ptr<Document>& document) override; 
};

class RemoveSlide : public IAction {
    std::shared_ptr<Slide> slide;
    size_t slideNumber;
public:
    RemoveSlide(const std::shared_ptr<Slide>& slide, size_t slideNumber);
    std::shared_ptr<IAction> execute(std::shared_ptr<Document>& document) override; 
};

class ChangeItem : public IAction {
    std::shared_ptr<Item> item;
    size_t slideNumber;
public:
    ChangeItem(const std::shared_ptr<Item>& item, size_t slideNumber);
    std::shared_ptr<IAction> execute(std::shared_ptr<Document>& document) override; 
};


#endif
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
#include "Data/View.hpp"
#include "Serialization/Converter.hpp"
#include "Serialization/SaveLoad.hpp"
#include "Interfaces/IModifierAction.hpp"

// RemoveItem, RemoveSlide, DisplayItem, DisplaySlide, ChangeItem, List, Next, Prev



class AddItem : public IModifierAction {
    std::shared_ptr<Item> item;
public:
    AddItem(const std::shared_ptr<Item>& item);
    std::shared_ptr<IModifierAction> execute(std::shared_ptr<Document>& document) override; // current slide index is in item
};

class AddSlide : public IModifierAction {
    std::shared_ptr<Slide> slide;
public:
    AddSlide(const std::shared_ptr<Slide>& slide);
    std::shared_ptr<IModifierAction> execute(std::shared_ptr<Document>& document) override; 
};

class RemoveItem : public IModifierAction {
    std::shared_ptr<Item> item;
public:
    RemoveItem(const std::shared_ptr<Item>& item);
    std::shared_ptr<IModifierAction> execute(std::shared_ptr<Document>& document) override; 
};

class RemoveSlide : public IModifierAction {
    size_t slideNumber;
public:
    RemoveSlide(const size_t slideNumber);
    std::shared_ptr<IModifierAction> execute(std::shared_ptr<Document>& document) override; 
};

class ChangeItem : public IModifierAction {
    std::shared_ptr<Item> item;
public:
    ChangeItem(const std::shared_ptr<Item>& item);
    std::shared_ptr<IModifierAction> execute(std::shared_ptr<Document>& document) override; 
};

class List : public IRendererAction {
    std::shared_ptr<Document> document;
public:
    List(const std::shared_ptr<Document>& document);
    void execute() override; 
};

class DisplayItem : public IRendererAction {
    size_t itemIndex;
public:
    DisplayItem(const size_t& itemIndex);
    void execute() override; 
};

class DisplaySlide : public IRendererAction {
    std::shared_ptr<Slide> slide;
public:
    DisplaySlide(const std::shared_ptr<Slide>& slide);
    void execute() override; 
};




// class DisplayAction : public Action {
//     std::unordered_map<std::string, std::vector<std::string>> operands;
//     void displayItem(const std::shared_ptr<Item>& item);
// public:
//     DisplayAction(const std::unordered_map<std::string, std::vector<std::string>>& operands);
//     std::shared_ptr<Action> execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) override;
// };

// class ChangeAction : public Action {
//     std::unordered_map<std::string, std::vector<std::string>> operands;

// public:
//     ChangeAction(const std::unordered_map<std::string, std::vector<std::string>>& operands);
//     std::shared_ptr<Action> execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) override;
// };

// class ListAction : public Action {
//     std::unordered_map<std::string, std::vector<std::string>> operands;

//     void displayItem(const std::shared_ptr<Item>& item);
// public:
//     ListAction(const std::unordered_map<std::string, std::vector<std::string>>& operands);
//     std::shared_ptr<Action> execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) override;
// };

// class NextAction : public Action {
//     std::unordered_map<std::string, std::vector<std::string>> operands;

// public:
//     NextAction(const std::unordered_map<std::string, std::vector<std::string>>& operands);
//     std::shared_ptr<Action> execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) override;
// };

// class PrevAction : public Action {
//     std::unordered_map<std::string, std::vector<std::string>> operands;

// public:
//     PrevAction(const std::unordered_map<std::string, std::vector<std::string>>& operands);
//     std::shared_ptr<Action> execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) override;
// };

// class SaveAction : public Action {
//     std::unordered_map<std::string, std::vector<std::string>> operands;

// public:
//     SaveAction(const std::unordered_map<std::string, std::vector<std::string>>& operands);
//     std::shared_ptr<Action> execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) override;
// };

// class LoadAction : public Action {
//     std::unordered_map<std::string, std::vector<std::string>> operands;

//     std::shared_ptr<Item> setItemAttribute(std::string_view file);
// public:
//     LoadAction(const std::unordered_map<std::string, std::vector<std::string>>& operands);
//     std::shared_ptr<Action> execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) override;
// };


#endif
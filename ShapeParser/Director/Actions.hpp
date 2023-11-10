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

class Action {
protected:
    std::unordered_map<std::string, std::vector<std::string>> operands;
public:
    Action() = default;
    Action(std::unordered_map<std::string, std::vector<std::string>>& operands);
    virtual std::shared_ptr<Action> execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) = 0;
    std::shared_ptr<Slide> getCurrentSlide(std::shared_ptr<Document>& document, size_t& currentSlideIndex) const;
    std::unordered_map<std::string, std::vector<std::string>> createOperands(const std::string& actionType, const std::vector<std::string>& operands);
};

class AddAction : public Action {
    std::shared_ptr<Item> createItem(const std::shared_ptr<Slide>& slide);
public:
    AddAction(std::unordered_map<std::string, std::vector<std::string>>& operands);
    std::shared_ptr<Action> execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) override;
};

class RemoveAction : public Action {
public:
    RemoveAction(std::unordered_map<std::string, std::vector<std::string>>& operands);
    std::shared_ptr<Action> execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) override;
};

class DisplayAction : public Action {
    void displayItem(const std::shared_ptr<Item>& item);
public:
    DisplayAction(std::unordered_map<std::string, std::vector<std::string>>& operands);
    std::shared_ptr<Action> execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) override;
};

class ChangeAction : public Action {
public:
    ChangeAction(std::unordered_map<std::string, std::vector<std::string>>& operands);
    std::shared_ptr<Action> execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) override;
};

class ListAction : public Action {
    void displayItem(const std::shared_ptr<Item>& item);
public:
    ListAction(std::unordered_map<std::string, std::vector<std::string>>& operands);
    std::shared_ptr<Action> execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) override;
};

class NextAction : public Action {
public:
    NextAction(std::unordered_map<std::string, std::vector<std::string>>& operands);
    std::shared_ptr<Action> execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) override;
};

class PrevAction : public Action {
public:
    PrevAction(std::unordered_map<std::string, std::vector<std::string>>& operands);
    std::shared_ptr<Action> execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) override;
};

class SaveAction : public Action {
public:
    SaveAction(std::unordered_map<std::string, std::vector<std::string>>& operands);
    std::shared_ptr<Action> execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) override;
};

class LoadAction : public Action {
    std::shared_ptr<Item> setItemAttribute(std::string_view file);
public:
    LoadAction(std::unordered_map<std::string, std::vector<std::string>>& operands);
    std::shared_ptr<Action> execute(std::shared_ptr<Document>& document, size_t& currentSlideIndex) override;
};


#endif
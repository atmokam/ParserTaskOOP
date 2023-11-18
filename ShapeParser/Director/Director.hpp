#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP

#include <string>

#include "Data/Document.hpp"
#include "Data/View.hpp"
#include "Interfaces/IDirector.hpp"
#include "ActionHistory.hpp"
#include "Interfaces/IModifierAction.hpp"
#include "Interfaces/IRendererAction.hpp"


class Director : public IDirector {
    std::shared_ptr<Document> document;
    size_t currentSlideIndex = 0;
    std::shared_ptr<Slide> currentSlide;  // new
    //std::unordered_map<std::string, std::vector<std::string>> operands;
    std::shared_ptr<ActionHistory> history; // shared so that i can later pass it to gui

public:
    
    Director();
    //void setOperands(std::unordered_map<std::string, std::vector<std::string>>& operands);
    //std::shared_ptr<Action> executeAction(const std::string& actionType) override;
    //void addActionToHistory(std::shared_ptr<Action> action) override;
    void doAction(std::shared_ptr<IModifierAction> action) override;
    void doAction(std::shared_ptr<IRendererAction> action) override;
    std::shared_ptr<Document> getDocument() override;
    std::shared_ptr<Slide> getCurrentSlide() override;
    size_t getCurrentSlideNumber() override;
    //void setCurrentSlideNumber(size_t currentSlideNumber) override;
    std::shared_ptr<ActionHistory> getHistory() override;
    void undo() override;
    void redo() override;
    void nextSlide() override;
    void previousSlide() override;


};




#endif
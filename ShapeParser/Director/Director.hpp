#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP

#include <string>

#include "Data/Document.hpp"
#include "Data/View.hpp"
#include "Interfaces/IDirector.hpp"
#include "ActionHistory.hpp"


class Director : public IDirector {
    std::shared_ptr<Document> document;
    size_t currentSlideIndex = 0;
    std::unordered_map<std::string, std::vector<std::string>> operands;
    ActionHistory history;

public:
    
    Director(std::unordered_map<std::string, std::vector<std::string>>& operands);
    std::shared_ptr<Action> executeAction(const std::string& actionType) override;
    void addActionToHistory(std::shared_ptr<Action> action) override;
    void undo() override;
    void redo() override;

};




#endif
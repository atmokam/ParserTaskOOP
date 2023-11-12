#ifndef ACTIONHISTORY_HPP
#define ACTIONHISTORY_HPP

#include <stack>

#include "Actions.hpp"

class ActionHistory {
    std::shared_ptr<Document> document;
    size_t currentSlideIndex;
    std::stack<std::shared_ptr<Action>> undoStack;
    std::stack<std::shared_ptr<Action>> redoStack;
public:
    ActionHistory(const std::shared_ptr<Document>& document, const size_t current);
    void addAction(std::shared_ptr<Action> action); // adds to undo stack
    void undo();
    void redo();
};

#endif
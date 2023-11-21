#ifndef ACTIONHISTORY_HPP
#define ACTIONHISTORY_HPP

#include <stack>

#include "Interfaces/IModifierAction.hpp"

class ActionHistory {
    std::shared_ptr<Document> document;
    size_t currentSlideIndex;
    std::stack<std::shared_ptr<IModifierAction>> undoStack;
    std::stack<std::shared_ptr<IModifierAction>> redoStack;
public:
    ActionHistory(const std::shared_ptr<Document>& document, const size_t current);
    void addAction(std::shared_ptr<IModifierAction> action); // adds to undo stack
    void undo();
    void redo();
};

#endif
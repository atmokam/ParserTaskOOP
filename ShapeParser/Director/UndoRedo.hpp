#ifndef UNDOREDO_HPP
#define UNDOREDO_HPP

#include <stack>

#include "Interfaces/IAction.hpp"

class UndoRedo {
    std::shared_ptr<Document> document;
    size_t currentSlideIndex;
    std::stack<std::shared_ptr<IAction>> undoStack;
    std::stack<std::shared_ptr<IAction>> redoStack;
public:
    UndoRedo(const std::shared_ptr<Document>& document, const size_t current);
    void addAction(std::shared_ptr<IAction> action); // adds to undo stack
    void undo();
    void redo();
};

#endif
#ifndef UNDOREDO_HPP
#define UNDOREDO_HPP

#include <stack>

#include "IAction.hpp"
#include "Include/IDocument.hpp"
#include "Data/Document.hpp"

class UndoRedo {
    IDocument& document;
    size_t currentSlideIndex;
    std::stack<std::shared_ptr<IAction>> undoStack;
    std::stack<std::shared_ptr<IAction>> redoStack;
public:
    UndoRedo(IDocument& document, const size_t current);
    void addAction(std::shared_ptr<IAction> action); // adds to undo stack
    void undo();
    void redo();
};

#endif
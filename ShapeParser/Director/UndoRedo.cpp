#include "UndoRedo.hpp"

UndoRedo::UndoRedo(std::shared_ptr<IDocument>& document, const size_t current) : document(document), currentSlideIndex(current){}

void UndoRedo::addAction(std::shared_ptr<IAction> action) {
    undoStack.push(action);
}

void UndoRedo::undo() {
    if (undoStack.empty()) {
        std::cout << "Nothing to undo" << std::endl;
        return;
    }
    std::shared_ptr<IAction> action = undoStack.top();
    std::cout << "Undoing action" << std::endl;
    undoStack.pop();
    redoStack.push(action->execute(document));
}


void UndoRedo::redo() {
    if (redoStack.empty()) {
        std::cout << "Nothing to redo" << std::endl;
        return;
    }
    std::shared_ptr<IAction> action = redoStack.top();
    std::cout << "Redoing action" << std::endl;
    
    redoStack.pop();
    undoStack.push(action->execute(document));
}

void UndoRedo::clearStack() {
    undoStack = std::stack<std::shared_ptr<IAction>>();
    redoStack = std::stack<std::shared_ptr<IAction>>();
}

void UndoRedo::newDocument(std::shared_ptr<IDocument>& document) {
    this->document = document;
}
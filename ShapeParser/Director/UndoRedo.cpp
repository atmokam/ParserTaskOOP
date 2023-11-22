#include "UndoRedo.hpp"

UndoRedo::UndoRedo(const std::shared_ptr<Document>& document, const size_t current) : document(document), currentSlideIndex(current){}

void UndoRedo::addAction(std::shared_ptr<IAction> action) {
    undoStack.push(action);
    std::cout << "Action added to history" << std::endl;
    undo();
}

void UndoRedo::undo() {
    if (undoStack.empty()) {
        std::cout << "Nothing to undo" << std::endl;
        return;
    }
    std::shared_ptr<IAction> action = undoStack.top();
    std::cout << "Undoing action" << std::endl;
    action->execute(document);
    undoStack.pop();
    redoStack.push(action);
}


void UndoRedo::redo() {
    if (redoStack.empty()) {
        std::cout << "Nothing to redo" << std::endl;
        return;
    }
    std::shared_ptr<IAction> action = redoStack.top();
    action->execute(document);
    redoStack.pop();
    undoStack.push(action);
}
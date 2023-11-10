#include "ActionHistory.hpp"

ActionHistory::ActionHistory(const std::shared_ptr<Document>& document, const size_t current) : document(document), currentSlideIndex(current){}

void ActionHistory::addAction(std::shared_ptr<Action> action) {
    undoStack.push(action);
}

void ActionHistory::undo() {
    if (undoStack.empty()) {
        std::cout << "Nothing to undo" << std::endl;
        return;
    }
    std::shared_ptr<Action> action = undoStack.top();
    action->execute(document, currentSlideIndex);
    undoStack.pop();
    redoStack.push(std::make_shared<Action>(action)); // for optimization purposes
}


void ActionHistory::redo() {
    if (redoStack.empty()) {
        std::cout << "Nothing to redo" << std::endl;
        return;
    }
    std::shared_ptr<Action> action = redoStack.top();
    action->execute(document, currentSlideIndex);
    redoStack.pop();
    undoStack.push(std::make_shared<Action>(action));
}
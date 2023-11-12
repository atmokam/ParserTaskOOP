#include "Director.hpp"

Director::Director() : document(std::make_shared<Document>()), history(std::make_unique<ActionHistory>(document, currentSlideIndex)) {}


std::shared_ptr<Action> Director::executeAction(const std::string& actionType) {
    std::shared_ptr<Action> action;
    if (actionType == "add") {
        action = std::make_shared<AddAction>(operands);
        std::cout << "Add action created" << std::endl;
    } else if (actionType == "remove") {
        action = std::make_shared<RemoveAction>(operands);
    // } else if (actionType == "display") {
    //     action = std::make_shared<DisplayAction>(operands);
    // } else if (actionType == "change") {
    //     action = std::make_shared<ChangeAction>(operands);
    // } else if (actionType == "list") {
    //     action = std::make_shared<ListAction>(operands);
    // } else if (actionType == "next") {
    //     action = std::make_shared<NextAction>(operands);
    // } else if (actionType == "prev") {
    //     action = std::make_shared<PrevAction>(operands);
    // } else if (actionType == "save") {
    //     action = std::make_shared<SaveAction>(operands);
    } else {
        throw std::runtime_error("Invalid action type");
    }
    return action->execute(document, currentSlideIndex);
}

void Director::addActionToHistory(std::shared_ptr<Action> action) {
    history->addAction(action);
}

void Director::undo() {
    history->undo();
}

void Director::redo() {
    history->redo();
}


void Director::setOperands(std::unordered_map<std::string, std::vector<std::string>>& operands) {
    this->operands = operands;
   
}


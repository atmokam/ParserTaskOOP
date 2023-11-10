#include "Director.hpp"

Director::Director(std::unordered_map<std::string, std::vector<std::string>>& operands) : document(std::make_shared<Document>()), operands(operands), history(document, currentSlideIndex) {}

std::shared_ptr<Action> Director::executeAction(const std::string& actionType) {
    std::shared_ptr<Action> action;
    if (actionType == "add") {
        action = std::make_shared<AddAction>(operands);
    } else if (actionType == "remove") {
        action = std::make_shared<RemoveAction>(operands);
    } else if (actionType == "display") {
        action = std::make_shared<DisplayAction>(operands);
    } else if (actionType == "change") {
        action = std::make_shared<ChangeAction>(operands);
    } else if (actionType == "list") {
        action = std::make_shared<ListAction>(operands);
    } else if (actionType == "next") {
        action = std::make_shared<NextAction>(operands);
    } else if (actionType == "prev") {
        action = std::make_shared<PrevAction>(operands);
    } else if (actionType == "save") {
        action = std::make_shared<SaveAction>(operands);
    } else {
        throw std::runtime_error("Invalid action type");
    }
    return action->execute(document, currentSlideIndex);
}

void Director::addActionToHistory(std::shared_ptr<Action> action) {
    history.addAction(action);
}



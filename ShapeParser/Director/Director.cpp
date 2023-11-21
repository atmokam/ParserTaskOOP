#include "Director.hpp"

Director::Director() : document(std::make_shared<Document>()), currentSlide(*document->begin()), history(std::make_shared<ActionHistory>(document, currentSlideIndex)) {}
                                                              // check if this works
std::shared_ptr<Document> Director::getDocument() {
    return document;
}

std::shared_ptr<Slide> Director::getCurrentSlide() {
    return currentSlide;
}

size_t Director::getCurrentSlideNumber() {
    return currentSlideIndex;
}

void Director::setCurrentSlideNumber(size_t currentSlideNumber) {
    currentSlideIndex = currentSlideNumber;
    currentSlide = document->getSlide(currentSlideIndex);
}

std::shared_ptr<ActionHistory> Director::getHistory() {
    return history;
}

void Director::doAction(std::shared_ptr<IModifierAction> action) {
    history->addAction(action->execute(document));
}

void Director::doAction(std::shared_ptr<IRendererAction> action) {
    action->execute();
}

void Director::undo() {
    history->undo();
}

void Director::redo() {
    history->redo();
}

void Director::nextSlide() {
    if (currentSlideIndex < document->size() - 1) {
        currentSlideIndex++;
        currentSlide = document->getSlide(currentSlideIndex);
    }
}

void Director::previousSlide() {
    if (currentSlideIndex > 0) {
        currentSlideIndex--;
        currentSlide = document->getSlide(currentSlideIndex);
    }
}



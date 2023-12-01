#include "Director.hpp"
#include "Data/Document.hpp"
#include "IAction.hpp"
#include "Data/Document.hpp"
#include "Director/Actions.hpp"
#include "Director/UndoRedo.hpp"


Director::Director() : document(std::make_shared<Document>()), currentSlide(*document->begin()), undoRedo(std::make_unique<UndoRedo>(document, currentSlideIndex)) {}
                                                              // check if this works
std::shared_ptr<IDocument>& Director::getDocument() {
    return document;
}

void Director::setDocument(std::shared_ptr<IDocument>& document){
    this->document = document;
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

std::unique_ptr<UndoRedo> Director::getUndoRedo() {
    return std::move(undoRedo);
}

void Director::clearUndoRedoStack() {
    undoRedo->newDocument(document);
    undoRedo->clearStack();
}

void Director::doAction(std::shared_ptr<IAction> action) {
    undoRedo->addAction(action->execute(document));
}

void Director::undo() {
    undoRedo->undo();
}

void Director::redo() {
    undoRedo->redo();
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



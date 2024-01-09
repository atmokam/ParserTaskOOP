#include <iostream>
#include "Director.hpp"
#include "Data/Document.hpp"
#include "IAction.hpp"
#include "Director/Actions.hpp"

namespace Director
{

    Director::Director() : document(std::make_shared<Data::Document>()) {}
                                                                
    std::shared_ptr<Data::IDocument> Director::getDocument() {
        return document;
    }

    void Director::setDocument(std::shared_ptr<Data::IDocument>& document){
        this->document = document;
    }

    std::shared_ptr<Data::Slide> Director::getCurrentSlide() {
        return document->getSlide(currentSlideIndex);
    }

    size_t Director::getCurrentSlideIndex() {
        return currentSlideIndex;
    }

    void Director::setCurrentSlideIndex(size_t currentSlideIndex) {
        this->currentSlideIndex = currentSlideIndex;
    }

    void Director::clearUndoRedoStack() {
        undoStack = std::stack<std::shared_ptr<IAction>>();
        redoStack = std::stack<std::shared_ptr<IAction>>();
    }

    void Director::doAction(std::shared_ptr<IAction> action) {
        addToUndoStack(action->execute(document));
    }


    void Director::undo() {
        if (undoStack.empty()) {
            std::cout << "Nothing to undo" << std::endl;
            return;
        }
        std::shared_ptr<IAction> action = undoStack.top();
        std::cout << "Undoing action" << std::endl;
        undoStack.pop();
        redoStack.push(action->execute(document));
    }


    void Director::redo() {
        if (redoStack.empty()) {
            std::cout << "Nothing to redo" << std::endl;
            return;
        }
        std::shared_ptr<IAction> action = redoStack.top();
        std::cout << "Redoing action" << std::endl;
        
        redoStack.pop();
        undoStack.push(action->execute(document));
    }

    void Director::addToUndoStack(std::shared_ptr<IAction> action) {
        undoStack.push(action);
    }


    bool Director::isDocumentModified() const 
    {
        return documentModified;
    }

    void Director::setDocumentModified(bool modified) 
    {
        documentModified = modified;
    }
}
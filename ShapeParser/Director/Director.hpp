#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP

#include <string>

#include "IDirector.hpp"
#include "UndoRedo.hpp"


class Director : public IDirector {
    // [TK] Document creation belongs to the application, director simply holds additional reference to it!
    std::shared_ptr<IDocument> document;
    size_t currentSlideIndex = 0;
    // [TK] Don't keep twice same thing, get current slide by currentSlideIndex whenever needed 
    // [TK] undoRedo should be siomple STL ciontainer, do not overdesing
    std::stack<std::shared_ptr<IAction>> undoStack;
    std::stack<std::shared_ptr<IAction>> redoStack;

private:
    void addToUndoStack(std::shared_ptr<IAction> action);

public:
    
    Director();
    // [TK] Good!
    void doAction(std::shared_ptr<IAction> action) override;
    void clearUndoRedoStack() override;
    std::shared_ptr<IDocument>& getDocument() override;
    void setDocument(std::shared_ptr<IDocument>& document) override;
    std::shared_ptr<Slide> getCurrentSlide() override;
    void setCurrentSlideIndex(size_t currentSlideIndex) override;
    size_t getCurrentSlideIndex() override;
    // [TK] Why we need this, UndoRedo is private internals of the director nobody should get it

    void undo() override;
    void redo() override;
    // [TK] Why we need this methods?


};




#endif

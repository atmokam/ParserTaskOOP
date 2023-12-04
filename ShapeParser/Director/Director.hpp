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
    std::shared_ptr<Slide> currentSlide;
    // [TK] undoRedo should be siomple STL ciontainer, do not overdesing
    std::unique_ptr<UndoRedo> undoRedo; // stacks

public:
    
    Director();
    // [TK] Good!
    void doAction(std::shared_ptr<IAction> action) override;
    void clearUndoRedoStack() override;
    std::shared_ptr<IDocument>& getDocument() override;
    void setDocument(std::shared_ptr<IDocument>& document) override;
    std::shared_ptr<Slide> getCurrentSlide() override;
    void setCurrentSlideNumber(size_t currentSlideNumber) override;
    size_t getCurrentSlideNumber() override;
    // [TK] Why we need this, UndoRedo is private internals of the director nobody should get it
    std::unique_ptr<UndoRedo> getUndoRedo() override;
    void undo() override;
    void redo() override;
    // [TK] Why we need this methods?
    void nextSlide() override;
    void previousSlide() override;


};




#endif

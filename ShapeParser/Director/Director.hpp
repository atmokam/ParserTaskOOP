#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP

#include <string>

#include "Data/Document.hpp"
#include "IDirector.hpp"
#include "UndoRedo.hpp"
#include "IAction.hpp"


class Director : public IDirector {
    std::shared_ptr<IDocument> document;
    size_t currentSlideIndex = 0;
    std::shared_ptr<Slide> currentSlide;  
    std::unique_ptr<UndoRedo> undoRedo; // stacks

public:
    
    Director();
    void doAction(std::shared_ptr<IAction> action) override;
    void clearUndoRedoStack() override;
    std::shared_ptr<IDocument>& getDocument() override;
    void setDocument(std::shared_ptr<IDocument>& document) override;
    std::shared_ptr<Slide> getCurrentSlide() override;
    void setCurrentSlideNumber(size_t currentSlideNumber) override;
    size_t getCurrentSlideNumber() override;
    std::unique_ptr<UndoRedo> getUndoRedo() override;
    void undo() override;
    void redo() override;
    void nextSlide() override;
    void previousSlide() override;


};




#endif
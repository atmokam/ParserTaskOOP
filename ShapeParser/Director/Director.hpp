#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP

#include <string>

#include "Data/Document.hpp"
#include "Interfaces/IDirector.hpp"
#include "UndoRedo.hpp"
#include "Interfaces/IAction.hpp"


class Director : public IDirector {
    std::shared_ptr<Document> document;
    size_t currentSlideIndex = 0;
    std::shared_ptr<Slide> currentSlide;  // new
    std::shared_ptr<UndoRedo> undoRedo; // shared so that i can later pass it to gui

public:
    
    Director();
    void doAction(std::shared_ptr<IAction> action) override;

    std::shared_ptr<Document> getDocument() override;
    std::shared_ptr<Slide> getCurrentSlide() override;
    void setCurrentSlideNumber(size_t currentSlideNumber) override;
    size_t getCurrentSlideNumber() override;
    std::shared_ptr<UndoRedo> getUndoRedo() override;
    void undo() override;
    void redo() override;
    void nextSlide() override;
    void previousSlide() override;


};




#endif
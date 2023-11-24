#ifndef IDIRECTOR_HPP
#define IDIRECTOR_HPP

#include <string>

#include "Data/Document.hpp"
#include "Director/Actions.hpp"
#include "Director/UndoRedo.hpp"

class IDirector {
public:
    
    virtual std::shared_ptr<Document> getDocument() = 0;
    virtual std::shared_ptr<Slide> getCurrentSlide() = 0;
    virtual size_t getCurrentSlideNumber() = 0;
    virtual void setCurrentSlideNumber(size_t currentSlideNumber) = 0;
    virtual void doAction(std::shared_ptr<IAction> action) = 0;
    virtual std::shared_ptr<UndoRedo> getUndoRedo() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual void nextSlide() = 0;
    virtual void previousSlide() = 0;

};

#endif

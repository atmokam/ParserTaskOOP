#ifndef IDIRECTOR_HPP
#define IDIRECTOR_HPP

#include <string>
#include <memory>

class IDocument;
class Slide;
class IAction;
class UndoRedo;

class IDirector {
public:
    
    virtual std::shared_ptr<IDocument>& getDocument() = 0;
    virtual void setDocument(std::shared_ptr<IDocument>& document) = 0;
    virtual std::shared_ptr<Slide> getCurrentSlide() = 0;
    virtual size_t getCurrentSlideIndex() = 0;
    virtual void setCurrentSlideIndex(size_t currentSlideIndex) = 0;
    virtual void doAction(std::shared_ptr<IAction> action) = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual void clearUndoRedoStack() = 0;

};

#endif

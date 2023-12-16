#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP

#include <string>
#include <memory>
#include <stack>

#include "IDirector.hpp"



class Director : public IDirector {
    std::shared_ptr<IDocument> document;
    size_t currentSlideIndex = 0;
    std::stack<std::shared_ptr<IAction>> undoStack;
    std::stack<std::shared_ptr<IAction>> redoStack;

    bool documentModified = false;

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

    void undo() override;
    void redo() override;

    bool isDocumentModified() const override;
    void setDocumentModified(bool modified) override;


};




#endif

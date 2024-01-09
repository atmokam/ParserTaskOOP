#ifndef IDIRECTOR_HPP
#define IDIRECTOR_HPP

#include <string>
#include <memory>

#include "Include/IDocument.hpp"
#include "Data/Slide.hpp"


namespace Director
{    
    class IAction;

    class IDirector {
    public:
        
        virtual std::shared_ptr<Data::IDocument> getDocument() = 0;
        virtual void setDocument(std::shared_ptr<Data::IDocument>& document) = 0;
        virtual std::shared_ptr<Data::Slide> getCurrentSlide() = 0;
        virtual size_t getCurrentSlideIndex() = 0;
        virtual void setCurrentSlideIndex(size_t currentSlideIndex) = 0;
        virtual void doAction(std::shared_ptr<IAction> action) = 0;
        virtual void undo() = 0;
        virtual void redo() = 0;
        virtual void clearUndoRedoStack() = 0;

        virtual bool isDocumentModified() const = 0;
        virtual void setDocumentModified(bool modified) = 0;

    };
}

#endif

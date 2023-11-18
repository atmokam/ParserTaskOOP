#ifndef IDIRECTOR_HPP
#define IDIRECTOR_HPP

#include <string>

#include "Data/Document.hpp"
#include "Director/Actions.hpp"
#include "Interfaces/IModifierAction.hpp"
#include "Interfaces/IRendererAction.hpp"


class IDirector {
public:
    
    //virtual std::shared_ptr<Action> executeAction(const std::string& actionType) = 0;
    //virtual void addActionToHistory(std::shared_ptr<Action> action) = 0;
    virtual void doAction(std::shared_ptr<IModifierAction> action) = 0;
    virtual void doAction(std::shared_ptr<IRendererAction> action) = 0;
    virtual std::shared_ptr<Document> getDocument() = 0;
    virtual std::shared_ptr<Slide> getCurrentSlide() = 0;
    virtual size_t getCurrentSlideNumber() = 0;
    //void setCurrentSlideNumber(size_t currentSlideNumber) override;
    virtual std::shared_ptr<ActionHistory> getHistory() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual void nextSlide() = 0;
    virtual void previousSlide() = 0;

};

#endif

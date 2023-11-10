#ifndef IDIRECTOR_HPP
#define IDIRECTOR_HPP

#include <string>

#include "Data/Document.hpp"
#include "Director/Actions.hpp"


class IDirector {
public:
    
    virtual std::shared_ptr<Action> executeAction(const std::string& actionType) = 0;
    virtual void addActionToHistory(std::shared_ptr<Action> action) = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;

};

#endif

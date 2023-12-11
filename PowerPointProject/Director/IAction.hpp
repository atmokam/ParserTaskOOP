#ifndef IACTION_HPP
#define IACTION_HPP

#include <memory>

class IDocument;

class IAction {
public:
    virtual std::shared_ptr<IAction> execute(std::shared_ptr<IDocument>& document) = 0;
};

#endif
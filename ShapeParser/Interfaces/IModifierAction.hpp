#ifndef IMODIFIERACTION_HPP
#define IMODIFIERACTION_HPP

#include <memory>
#include "Data/Document.hpp"


class IModifierAction {
public:
    virtual std::shared_ptr<IModifierAction> execute(std::shared_ptr<Document>& document) = 0;
};

#endif
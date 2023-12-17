#ifndef IACTION_HPP
#define IACTION_HPP

#include <memory>

#include "Include/IDocument.hpp"

namespace Director
{
    class IAction {
    public:
        virtual std::shared_ptr<IAction> execute(std::shared_ptr<Data::IDocument>& document) = 0;
    };
}

#endif
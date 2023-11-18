#ifndef IRENDERERACTION_HPP
#define IRENDERERACTION_HPP

#include <memory>
#include "Data/Document.hpp"

class IRendererAction {
public:
    virtual void execute() = 0;
};

#endif
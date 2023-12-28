#ifndef INNERMARGINCONSTANT_HPP
#define INNERMARGINCONSTANT_HPP

#include "Renderer/Shape/ShapeLibrary.hpp"

// Text's inner margin 

namespace Renderer
{

    class InnerMarginConstant
    {
        std::unordered_map<Renderer::Type, double> margin;
    public:
        InnerMarginConstant();
        double getMargins(Renderer::Type type) const;
    };
}

#endif
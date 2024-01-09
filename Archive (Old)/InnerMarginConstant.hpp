#ifndef INNERMARGINCONSTANT_HPP
#define INNERMARGINCONSTANT_HPP

#include "Renderer/Shape/ShapeLibrary.hpp"

// A constant that gets multipled by initial width and height to get the inscribed rectangle

// I don't know if this is overengineering or not, for the reason of possible change to constants I decided to make it a separate class.

namespace Renderer
{
    class InnerMarginConstant
    {
        std::unordered_map<Renderer::Type, double> margin;
    public:
        InnerMarginConstant();
        double getMargin(Renderer::Type type) const;
    };
}

#endif
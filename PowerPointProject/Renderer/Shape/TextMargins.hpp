#ifndef TEXTMARGINS_HPP
#define TEXTMARGINS_HPP

#include "Renderer/Shape/ShapeLibrary.hpp"

namespace Renderer
{

    class TextMargins
    {
        std::unordered_map<Renderer::Type, std::pair<double, double>> margins;
    public:
        TextMargins();
        std::pair<double, double> getMargins(Renderer::Type type) const;
    };
}

#endif
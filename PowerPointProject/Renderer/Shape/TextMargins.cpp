#include "TextMargins.hpp"

namespace Renderer
{
    TextMargins::TextMargins()
    {
        margins[Renderer::Type::Ellipse] = {0.7071, 0.7071};
        margins[Renderer::Type::Rectangle] = {1, 1};
        margins[Renderer::Type::Triangle] = {};
        margins[Renderer::Type::Trapezoid] = {};
        margins[Renderer::Type::Line] = {};
    }

    std::pair<double, double> TextMargins::getMargins(Renderer::Type type) const
    {
        return margins.at(type);
    }
}
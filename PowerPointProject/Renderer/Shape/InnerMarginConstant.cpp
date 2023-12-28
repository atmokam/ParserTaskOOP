#include "InnerMarginConstant.hpp"

namespace Renderer
{
    InnerMarginConstant::InnerMarginConstant()
    {
        margin[Renderer::Type::Ellipse] = 0.7071;
        margin[Renderer::Type::Rectangle] = 1;
        margin[Renderer::Type::Triangle] = {};
        margin[Renderer::Type::Trapezoid] = {};
        margin[Renderer::Type::Line] = {};
    }

    double InnerMarginConstant::getMargins(Renderer::Type type) const
    {
        return margin.at(type);
    }
}
#ifndef SHAPETEXT_HPP
#define SHAPETEXT_HPP

#include <memory>

#include "ShapeBase.hpp"
#include "IVisualDisplayable.hpp"

//                             Intent: wrapper class for shape text rendering

class QPainter;
class QRect;
class QTextOption;

namespace Renderer
{
    class ShapeText : public ShapeBase, public IVisualDisplayable
    {
        std::shared_ptr<ShapeBase> shape;
        std::unordered_map<Renderer::Type, double> marginConstants;

        void drawText(QPainter& painter, Formatting::DimentionConverter& converter);
        void setupTextAttributes(QRect& rect, QPainter& painter, QTextOption& option);
    public:
        ShapeText(std::shared_ptr<ShapeBase> shape);
        void draw(QPainter& painter, Formatting::DimentionConverter& converter) override;
    };

}


#endif
#ifndef SHAPETEXTVISITOR_HPP
#define SHAPETEXTVISITOR_HPP

#include "ShapeBase.hpp"
#include "IShapeVisitor.hpp"
#include "../Formatting/DimentionConverter.hpp"
#include <QPainter>

namespace Renderer
{
    class ShapeTextVisitor : public IShapeVisitor
    {
        QPainter& painter;
        Formatting::DimentionConverter& converter;

        QRect getRect(std::shared_ptr<ShapeBase> shape) const;
        void setupTextAttributes(std::shared_ptr<ShapeBase> shape, QRect& rect);
    public:
        ShapeTextVisitor(QPainter& painter, Formatting::DimentionConverter& converter);
        void visit(ShapeEllipse& shape) override;
        void visit(ShapeRectangle& shape) override;
        void visit(ShapeTriangle& shape) override;
        void visit(ShapeTrapezoid& shape) override;
        void visit(ShapeLine& shape) override;
    };
}


#endif
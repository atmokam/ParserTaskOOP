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

        QRect getInnerRect(std::shared_ptr<ShapeBase> shape) const;
        void setupTextAttributes(std::shared_ptr<ShapeBase> shape, QRect& rect);

        void printTextForShape(std::shared_ptr<ShapeBase> shape);
    public:
        ShapeTextVisitor(QPainter& painter, Formatting::DimentionConverter& converter);
        void visit(ShapeEllipse& shape) override;
        void visit(ShapeRectangle& shape) override;
        void visit(ShapeTriangle& shape) override;
        void visit(ShapeTrapezoid& shape) override;
        void visit(ShapeLine& shape) override;

        void printText(std::shared_ptr<IShape> shape);
    };
}


#endif
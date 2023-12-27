#ifndef ISHAPEVISITOR_HPP
#define ISHAPEVISITOR_HPP

namespace Renderer
{
    class ShapeEllipse;
    class ShapeRectangle;
    class ShapeTriangle;
    class ShapeTrapezoid;
    class ShapeLine;

    class IShapeVisitor
    {
    public:
        virtual void visit(ShapeEllipse& shape) = 0;
        virtual void visit(ShapeRectangle& shape) = 0;
        virtual void visit(ShapeTriangle& shape) = 0;
        virtual void visit(ShapeTrapezoid& shape) = 0;
        virtual void visit(ShapeLine& shape) = 0;
    };
}

#endif
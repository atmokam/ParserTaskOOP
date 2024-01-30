#ifndef INSCRIBEDRECTANGLE_HPP
#define INSCRIBEDRECTANGLE_HPP

#include "ShapeLibrary.hpp"
#include "ShapeBase.hpp"

#include "../Formatting/DimentionConverter.hpp"
#include <unordered_map>
#include <QRect>


namespace Renderer
{
    class InscribedRectangleCalc
    {
        std::shared_ptr<ShapeBase> shape;
        std::shared_ptr<QRect> rect;
        std::shared_ptr<Formatting::DimentionConverter> converter;

        std::unordered_map<Renderer::Type, double> marginConstants;

        void calculateDefaultWay();

    public:
        InscribedRectangleCalc(std::shared_ptr<ShapeBase> shape, Formatting::DimentionConverter& converter);

        void visit(ShapeEllipse& shape) override;
        void visit(ShapeRectangle& shape) override;
        void visit(ShapeTriangle& shape) override;
        void visit(ShapeTrapezoid& shape) override;
        void visit(ShapeLine& shape) override; // this one's a line, so it won't inscribe (just gets text bounds)

        void calculateTextRect();
        QRect getRect() const;
    };
}
#endif

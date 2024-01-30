#include "InscribedRectangleCalc.hpp"
#include <iostream>

namespace Renderer
{
    InscribedRectangleCalc::InscribedRectangleCalc(std::shared_ptr<ShapeBase> shape, Formatting::DimentionConverter& converter) : shape(shape),
     converter(std::make_shared<Formatting::DimentionConverter>(converter)), rect(std::make_shared<QRect>())
    {
        marginConstants[Renderer::Type::Ellipse] = 0.7071;
        marginConstants[Renderer::Type::Rectangle] = 1;
        marginConstants[Renderer::Type::Triangle] = {};
        marginConstants[Renderer::Type::Trapezoid] = 0.3333;
    }


    void InscribedRectangleCalc::calculateTextRect()
    {
        shape->accept(std::make_shared<InscribedRectangleCalc>(*this));
    }

    void InscribedRectangleCalc::visit(ShapeEllipse& shape) 
    {
        calculateDefaultWay();
    }

    void InscribedRectangleCalc::visit(ShapeRectangle& shape) 
    {
        calculateDefaultWay();
    }

    void InscribedRectangleCalc::visit(ShapeTriangle& shape) 
    {
        // triangle
    }

    void InscribedRectangleCalc::visit(ShapeTrapezoid& shape) 
    {
        //trapezoid
    }

    void InscribedRectangleCalc::visit(ShapeLine& shape) 
    {
        // line
    }


    void InscribedRectangleCalc::calculateDefaultWay()
    {
        auto item = shape->getItem();
        auto geometry = item->getGeometry();

        auto margin = marginConstants.at(item->getType());

        auto coordinates = geometry.getPosition().value().getCoordinates();
        auto width = geometry.getWidth().value();
        auto height = geometry.getHeight().value();

        auto newWidth = width * margin;
        auto newHeight = height * margin;

        auto x = coordinates[0] + double(width - newWidth)/2;
        auto y = coordinates[1] + double(height - newHeight)/2;

        *rect = QRect(converter->toPixels(x), converter->toPixels(y),
         converter->toPixels(newWidth), converter->toPixels(newHeight));

    }

    QRect InscribedRectangleCalc::getRect() const
    {
        return *rect;
    }

}
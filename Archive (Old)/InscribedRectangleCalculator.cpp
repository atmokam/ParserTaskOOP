#include "InscribedRectangleCalculator.hpp"
#include "InnerMarginConstant.hpp"
#include "ShapeBase.hpp"
#include "../Formatting/DimentionConverter.hpp"

#include <QRect>

#include "ShapeBase.hpp"

namespace Renderer
{

    QRect InscribedRectangleCalculator::calculateRectangle(std::shared_ptr<ShapeBase> shape, Formatting::DimentionConverter& converter)
    {
        InnerMarginConstant marginConstant;
        auto item = shape->getItem();
        auto geometry = item->getGeometry();

        auto margin = marginConstant.getMargin(item->getType());
        auto coordinates = geometry.getPosition().value().getCoordinates();
        auto width = geometry.getWidth().value();
        auto height = geometry.getHeight().value();

        auto newWidth = width * margin;
        auto newHeight = height * margin;

        auto x = coordinates[0] + double(width - newWidth)/2;
        auto y = coordinates[1] + double(height - newHeight)/2;

        QRect rect = QRect(converter.toPixels(x), converter.toPixels(y),
         converter.toPixels(newWidth), converter.toPixels(newHeight));

        return rect;
    }
}
#include "ShapeTextVisitor.hpp"
#include "TextMargins.hpp"
#include "../VisualConversion/TextFontAdjuster.hpp"

namespace Renderer
{
    ShapeTextVisitor::ShapeTextVisitor(QPainter& painter, Formatting::DimentionConverter& converter) : painter(painter), converter(converter)
    {}


    void ShapeTextVisitor::visit(ShapeEllipse& shape)
    {
        auto shapePtr = std::make_shared<ShapeEllipse>(shape);
        auto rect = getRect(shapePtr); // inner rect
        setupTextAttributes(shapePtr, rect);
       
        QTextOption option(Qt::AlignCenter);
        option.setWrapMode(QTextOption::WordWrap);

        painter.drawText(rect, QString::fromStdString(shape.getItem()->getAttributes().getText().value()), option);
    }

    void ShapeTextVisitor::visit(ShapeRectangle& shape)
    {

    }

    void ShapeTextVisitor::visit(ShapeTriangle& shape)
    {

    }

    void ShapeTextVisitor::visit(ShapeTrapezoid& shape)
    {

    }

    void ShapeTextVisitor::visit(ShapeLine& shape)
    {

    }

    
    QRect ShapeTextVisitor::getRect(std::shared_ptr<ShapeBase> shape) const
    {
        TextMargins marginConstants;
        auto item = shape->getItem();
        auto margins = marginConstants.getMargins(item->getType());
        auto geometry = item->getGeometry();
        auto coordinates = geometry.getPosition().value().getCoordinates();
        auto width = geometry.getWidth().value();
        auto height = geometry.getHeight().value();

        auto newWidth = width * margins.first;
        auto newHeight = height * margins.second;

        auto x = coordinates[0] + double(width - newWidth)/2;
        auto y = coordinates[1] + double(height - newHeight)/2;

        QRect rect = QRect(converter.toPixels(x), converter.toPixels(y),
         converter.toPixels(newWidth), converter.toPixels(newHeight));

        return rect;
    }

    void ShapeTextVisitor::setupTextAttributes(std::shared_ptr<ShapeBase> shape, QRect& rect)
    {
        auto text = shape->getItem()->getAttributes().getText();
        QString qText(QString::fromStdString(text.value()));

        auto fontSize = shape->getItem()->getAttributes().getFontSize().value();
        TextFontAdjuster fontAdjuster; // adjusts according to wordwrap
        QFont font("Arial", fontSize);
        fontAdjuster.adjustFont(font, rect, qText);
        painter.setFont(font);        
    }

}
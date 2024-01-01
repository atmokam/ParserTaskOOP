#include "ShapeTextVisitor.hpp"
#include "InnerMarginConstant.hpp"
#include "../VisualConversion/TextFontAdjuster.hpp"
#include "InscribedRectangleCalculator.hpp"

namespace Renderer
{
    ShapeTextVisitor::ShapeTextVisitor(QPainter& painter, Formatting::DimentionConverter& converter) 
    : painter(painter), converter(converter){}



    void ShapeTextVisitor::printText(std::shared_ptr<IShape> shape)
    {
        shape->accept(std::make_shared<ShapeTextVisitor>(*this));
    }


    void ShapeTextVisitor::visit(ShapeEllipse& shape)
    {
        auto shapePtr = std::make_shared<ShapeEllipse>(shape);
        printTextForShape(shapePtr);
    }

    void ShapeTextVisitor::visit(ShapeRectangle& shape)
    {
        auto shapePtr = std::make_shared<ShapeRectangle>(shape);
        printTextForShape(shapePtr);
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

    
    void ShapeTextVisitor::printTextForShape(std::shared_ptr<ShapeBase> shape)
    {
        auto rect = getInnerRect(shape); 
        setupTextAttributes(shape, rect);
       
        QTextOption option(Qt::AlignCenter);
        option.setWrapMode(QTextOption::WordWrap);

        auto text = QString::fromStdString(shape->getItem()->getAttributes().getText().value());
        painter.drawText(rect, text, option);
    
    }
    
    QRect ShapeTextVisitor::getInnerRect(std::shared_ptr<ShapeBase> shape) const
    {
        InscribedRectangleCalculator calculator;
        return calculator.calculateRectangle(shape, converter);
    }

    void ShapeTextVisitor::setupTextAttributes(std::shared_ptr<ShapeBase> shape, QRect& rect)
    {
        auto text = shape->getItem()->getAttributes().getText();
        QString qText(QString::fromStdString(text.value()));

        auto fontSize = shape->getItem()->getAttributes().getFontSize().value();
        TextFontAdjuster fontAdjuster; 
        QFont font("Arial", fontSize);

        fontAdjuster.adjustFont(font, rect, qText);
        painter.setFont(font);        
    }


}
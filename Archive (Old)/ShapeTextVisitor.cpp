#include "ShapeTextVisitor.hpp"
#include "../VisualConversion/TextFontAdjuster.hpp"
#include "InscribedRectangleCalc.hpp"

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
        InscribedRectangleCalc calculator(shape, converter);
        calculator.calculateTextRect();
        return calculator.getRect();
    }

    void ShapeTextVisitor::setupTextAttributes(std::shared_ptr<ShapeBase> shape, QRect& rect)
    {
        auto item = shape->getItem();
        auto text = item->getAttributes().getText();
        QString qText(QString::fromStdString(text.value()));

        auto fontSize = item->getAttributes().getFontSize().value();
        TextFontAdjuster fontAdjuster; 
        QFont font("Arial", fontSize);

        fontAdjuster.adjustFont(font, rect, qText);
        painter.setFont(font);        
    }


}
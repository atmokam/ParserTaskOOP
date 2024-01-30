#include "ShapeText.hpp"

#include <QPainter>
#include <QTextOption>

#include "Data/Item/ItemBase.hpp"
#include "Data/Item/ItemAttributes.hpp"
#include "ShapeLibrary.hpp"
#include "Serialization/Converter.hpp"
#include "../Formatting/DimentionConverter.hpp"
#include "Renderer/VisualConversion/QtConverter.hpp"
#include "../VisualConversion/TextFontAdjuster.hpp"

namespace Renderer
{
    
    ShapeText::ShapeText(std::shared_ptr<ShapeBase> shape) : shape(shape), ShapeBase(*shape)
    {
        marginConstants[Renderer::Type::Ellipse] = 0.7071;
        marginConstants[Renderer::Type::Rectangle] = 1;
        marginConstants[Renderer::Type::Triangle] = {};
        marginConstants[Renderer::Type::Trapezoid] = 0.3333;
    }

    void ShapeText::draw(QPainter& painter, Formatting::DimentionConverter& converter) 
    {
        auto visualShape = std::dynamic_pointer_cast<IVisualDisplayable>(shape);
        visualShape->draw(painter, converter);

        drawText(painter, converter);
    }

    void ShapeText::setupTextAttributes(QRect& rect, QPainter& painter, QTextOption& option)
    {
        auto item = shape->getItem();
        auto text = item->getAttributes().getText();
        QString qText(QString::fromStdString(text.value()));

        auto fontSize = item->getAttributes().getFontSize().value();
        QFont font("Arial", fontSize);

        TextFontAdjuster fontAdjuster; 
        fontAdjuster.adjustFont(font, rect, qText);
        painter.setFont(font);

        option = QTextOption(Qt::AlignCenter);
        option.setWrapMode(QTextOption::WordWrap);
    }

    
    void ShapeText::drawText(QPainter& painter, Formatting::DimentionConverter& converter)
    {
        auto item = shape->getItem();
        auto rect = getInnerTextRect(converter, marginConstants.at(item->getType())); 
        QTextOption option;
        setupTextAttributes(rect, painter, option);
        auto text = QString::fromStdString(item->getAttributes().getText().value());
        painter.drawText(rect, text, option);
    }
    
}
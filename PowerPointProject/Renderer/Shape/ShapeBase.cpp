#include <vector>
#include <QPainter>
#include <QPen>
#include <QFont>
#include <QTextOption>
#include "ShapeBase.hpp"
#include "Data/ItemBase.hpp"
#include "Data/ItemAttributes.hpp"
#include "Serialization/Converter.hpp"
#include "../Formatting/DimentionConverter.hpp"
#include "Renderer/VisualConversion/QtConverter.hpp"
#include "../VisualConversion/TextFontAdjuster.hpp"

namespace Renderer
{
    ShapeBase::ShapeBase(std::shared_ptr<Data::ItemBase> item) : item(item) {}

    void ShapeBase::print(std::ostream& stream) 
    {
        Serialization::Converter converter;
        stream << "Shape: " << converter.convertToString(item->getType()) << std::endl;
        stream << "---Geometry---" << std::endl;
        stream << "Position: " << converter.convertToString(item->getGeometry().getPosition().value()) << std::endl;
        stream << "Height: " << item->getGeometry().getHeight().value() << std::endl;
        stream << "Width: "<< item->getGeometry().getWidth().value() << std::endl;
        stream << "---Attributes---" << std::endl;
        stream << "FillColor: " << item->getAttributes().getHexFillColor().value() << std::endl;
        stream << "LineColor: " << item->getAttributes().getHexLineColor().value() << std::endl;
        stream << "LineWidth: " << item->getAttributes().getLineWidth().value() << std::endl;
        stream << "LineType: " << converter.convertToString(item->getAttributes().getLineType().value()) << std::endl;
        stream << "Text: " << item->getAttributes().getText().value() << std::endl;
    }

 
    std::shared_ptr<IShape> ShapeBase::clone(std::shared_ptr<Data::ItemBase> item)
    {
        setItem(item);
        return std::make_shared<ShapeBase>(*this);
    }

    void ShapeBase::setItem(std::shared_ptr<Data::ItemBase> item)
    {
        this->item = item;
    }


    void ShapeBase::setPainterAttributes(QPainter& painter)
    {
        QtConverter styleConverter;
        Serialization::Converter typeConverter;

        QColor lineColorValue = item->getAttributes().getHexLineColor().value();
        qreal lineWidthValue = item->getAttributes().getLineWidth().value();
        auto lineType = item->getAttributes().getLineType();
        Qt::PenStyle lineTypeValue = styleConverter.convertToQtPenStyle(typeConverter.convertToString(lineType.value())); // linetype could have had a tostring function so i wouldnt have to convert it all the time
                                                                                                                        // or i could have kept it as a string all along
        auto pen = QPen(lineColorValue, lineWidthValue, lineTypeValue);
        auto fillColor = item->getAttributes().getHexFillColor();
        auto brush = QBrush(QColor((fillColor.has_value()) ? fillColor.value() : Qt::transparent)); //TODO: make a way to remove the fill color or the line color after it has been set
        painter.setPen(pen);
        painter.setBrush(brush);
           
    }

    QRect ShapeBase::getRect(Formatting::DimentionConverter& converter) //
    {
        auto coordinates = item->getGeometry().getPosition().value().getCoordinates();
        auto height = item->getGeometry().getHeight().value();
        auto width = item->getGeometry().getWidth().value();
        QRect rect(converter.toPixels(coordinates[0]), converter.toPixels(coordinates[1]), 
            converter.toPixels(width), converter.toPixels(height));
        return rect;
    }






    // visual displayables

    ShapeRectangle::ShapeRectangle(std::shared_ptr<Data::ItemBase> item) : ShapeBase(item) {}

    void ShapeRectangle::draw(QPainter& painter, Formatting::DimentionConverter& converter) 
    {
        setPainterAttributes(painter);
        
        QRect rect = getRect(converter);

        auto text = item->getAttributes().getText();
        QString qText(QString::fromStdString(text.value()));

        auto fontSize = item->getAttributes().getFontSize().value();
        TextFontAdjuster fontAdjuster; // adjusts according to wordwrap
        QFont font("Arial", fontSize);
        fontAdjuster.adjustFont(font, rect, qText);
        painter.setFont(font); 

        QTextOption option(Qt::AlignCenter);
        option.setWrapMode(QTextOption::WordWrap);

        painter.drawRect(rect);
        painter.drawText(rect, QString::fromStdString(text.value()), option);
    }

    std::shared_ptr<IShape> ShapeRectangle::clone(std::shared_ptr<Data::ItemBase> item)
    {
        setItem(item);
        return std::make_shared<ShapeRectangle>(*this);
    }





    ShapeEllipse::ShapeEllipse(std::shared_ptr<Data::ItemBase> item) : ShapeBase(item) {}

    void ShapeEllipse::draw(QPainter& painter, Formatting::DimentionConverter& converter) 
    {
        setPainterAttributes(painter);
        
        QRect rect = getRect(converter);

        auto text = item->getAttributes().getText();
        QString qText(QString::fromStdString(text.value()));

        // create a rect that should set the margins for the text

        auto fontSize = item->getAttributes().getFontSize().value();
        TextFontAdjuster fontAdjuster; // adjusts according to wordwrap
        QFont font("Arial", fontSize);
        fontAdjuster.adjustFont(font, rect, qText);
        painter.setFont(font);

        QTextOption option(Qt::AlignCenter);
        option.setWrapMode(QTextOption::WordWrap);

        

        painter.drawEllipse(rect);
        painter.drawText(rect, QString::fromStdString(text.value()), option);
    }

    std::shared_ptr<IShape> ShapeEllipse::clone(std::shared_ptr<Data::ItemBase> item)
    {
        setItem(item);
        return std::make_shared<ShapeEllipse>(*this);
    }





    ShapeLine::ShapeLine(std::shared_ptr<Data::ItemBase> item) : ShapeBase(item) {}

    void ShapeLine::draw(QPainter& painter, Formatting::DimentionConverter& converter) 
    {
        setPainterAttributes(painter);

        auto points = item->getGeometry().getPosition().value().getCoordinates();

        painter.drawLine(converter.toPixels(points[0]), converter.toPixels(points[1]), 
            converter.toPixels(points[2]), converter.toPixels(points[3]));
    }

    std::shared_ptr<IShape> ShapeLine::clone(std::shared_ptr<Data::ItemBase> item)
    {
        setItem(item);
        return std::make_shared<ShapeLine>(*this);
    }





    ShapeTrapezoid::ShapeTrapezoid(std::shared_ptr<Data::ItemBase> item) : ShapeBase(item) {}

    void ShapeTrapezoid::draw(QPainter& painter, Formatting::DimentionConverter& converter) 
    {
        
    }

    std::shared_ptr<IShape> ShapeTrapezoid::clone(std::shared_ptr<Data::ItemBase> item)
    {
        setItem(item);
        return std::make_shared<ShapeTrapezoid>(*this);
    }





    ShapeTriangle::ShapeTriangle(std::shared_ptr<Data::ItemBase> item) : ShapeBase(item) {}

    void ShapeTriangle::draw(QPainter& painter, Formatting::DimentionConverter& converter) 
    {
        
    }

    std::shared_ptr<IShape> ShapeTriangle::clone(std::shared_ptr<Data::ItemBase> item)
    {
        setItem(item);
        return std::make_shared<ShapeTriangle>(*this);
    }

}

#include <vector>
#include <QPainter>
#include <QPen>
#include <QFont>
#include <QTextOption>
#include "ShapeBase.hpp"
#include "Data/Item/ItemBase.hpp"
#include "Data/Item/ItemAttributes.hpp"
#include "Serialization/Converter.hpp"
#include "../Formatting/DimentionConverter.hpp"
#include "Renderer/VisualConversion/QtConverter.hpp"
#include "../VisualConversion/TextFontAdjuster.hpp"

namespace Renderer
{


    // visual displayables
    ShapeRectangle::ShapeRectangle(std::shared_ptr<Data::ItemBase> item) : ShapeBase(item) {}

    void ShapeRectangle::draw(QPainter& painter, Formatting::DimentionConverter& converter) 
    {
        setPainterAttributes(painter);
        QRect rect = getRect(converter);
        painter.drawRect(rect);
    }

    std::shared_ptr<ICloneable> ShapeRectangle::clone(std::shared_ptr<Data::ItemBase> item)
    {
        setItem(item);
        return std::make_shared<ShapeRectangle>(*this);
    }

   




    ShapeEllipse::ShapeEllipse(std::shared_ptr<Data::ItemBase> item) : ShapeBase(item) {}

    void ShapeEllipse::draw(QPainter& painter, Formatting::DimentionConverter& converter) 
    {
        setPainterAttributes(painter);
        QRect rect = getRect(converter);       
        painter.drawEllipse(rect);
    }

    std::shared_ptr<ICloneable> ShapeEllipse::clone(std::shared_ptr<Data::ItemBase> item)
    {
        setItem(item);
        return std::make_shared<ShapeEllipse>(*this);
    }

  




    ShapeLine::ShapeLine(std::shared_ptr<Data::ItemBase> item) : ShapeBase(item) {}

    void ShapeLine::draw(QPainter& painter, Formatting::DimentionConverter& converter) 
    {
        setPainterAttributes(painter);

        auto geometry = item->getGeometry();
        auto points = geometry.getPosition().value().getCoordinates();

        painter.drawLine(converter.toPixels(points[0]), converter.toPixels(points[1]), 
            converter.toPixels(points[2]), converter.toPixels(points[3]));
    }

    std::shared_ptr<ICloneable> ShapeLine::clone(std::shared_ptr<Data::ItemBase> item)
    {
        setItem(item);
        return std::make_shared<ShapeLine>(*this);
    }

   




    ShapeTrapezoid::ShapeTrapezoid(std::shared_ptr<Data::ItemBase> item) : ShapeBase(item) {}

    void ShapeTrapezoid::draw(QPainter& painter, Formatting::DimentionConverter& converter) 
    {
        QPolygon trapezoid;
        auto geometry = item->getGeometry();

        auto points = geometry.getPosition().value().getCoordinates();
        auto x = converter.toPixels(points[0]);
        auto y = converter.toPixels(points[1]);
        
        auto width = converter.toPixels(geometry.getWidth().value());      
        auto height = converter.toPixels(geometry.getHeight().value());

       
        trapezoid << QPoint(x, y + height) 
         << QPoint(x + width, y + height)
         << QPoint(x + (width-(width/3.0)), y) 
         << QPoint(x + (width/3.0), y);

        painter.drawPolygon(trapezoid);
    }

    std::shared_ptr<ICloneable> ShapeTrapezoid::clone(std::shared_ptr<Data::ItemBase> item)
    {
        setItem(item);
        return std::make_shared<ShapeTrapezoid>(*this);
    }

    





    ShapeTriangle::ShapeTriangle(std::shared_ptr<Data::ItemBase> item) : ShapeBase(item) {}

    void ShapeTriangle::draw(QPainter& painter, Formatting::DimentionConverter& converter) 
    {
        
    }

    std::shared_ptr<ICloneable> ShapeTriangle::clone(std::shared_ptr<Data::ItemBase> item)
    {
        setItem(item);
        return std::make_shared<ShapeTriangle>(*this);
    }

    


    // text displayable
    ShapeBase::ShapeBase(std::shared_ptr<Data::ItemBase> item) : item(item) {}

    void ShapeBase::print(std::ostream& stream) 
    {
        Serialization::Converter converter;
        auto attributes = item->getAttributes();
        auto geometry = item->getGeometry();

        stream << "Shape: " << converter.convertToString(item->getType()) << std::endl;
        stream << "---Geometry---" << std::endl;
        stream << "Position: " << converter.convertToString(geometry.getPosition().value()) << std::endl;
        stream << "Height: " << geometry.getHeight().value() << std::endl;
        stream << "Width: "<< geometry.getWidth().value() << std::endl;
        stream << "---Attributes---" << std::endl;
        stream << "FillColor: " << attributes.getHexFillColor().value() << std::endl;
        stream << "LineColor: " << attributes.getHexLineColor().value() << std::endl;
        stream << "LineWidth: " << attributes.getLineWidth().value() << std::endl;
        stream << "LineType: " << converter.convertToString(attributes.getLineType().value()) << std::endl;
        stream << "Text: " << attributes.getText().value() << std::endl;
        stream << std::endl;
    }

 
    std::shared_ptr<ICloneable> ShapeBase::clone(std::shared_ptr<Data::ItemBase> item)
    {
        setItem(item);
        return std::make_shared<ShapeBase>(*this);
    }

    void ShapeBase::setItem(std::shared_ptr<Data::ItemBase> item)
    {
        this->item = item;
    }

    std::shared_ptr<Data::ItemBase> ShapeBase::getItem() const
    {
        return item;
    }





    void ShapeBase::setPainterAttributes(QPainter& painter)
    {
        QtConverter styleConverter;
        Serialization::Converter typeConverter;

        auto attributes = item->getAttributes();

        auto lineType = attributes.getLineType();
        QColor qlineColor = attributes.getHexLineColor().value();
        qreal qlineWidth = attributes.getLineWidth().value();
        Qt::PenStyle qlineType = styleConverter.convertToQtPenStyle(
            typeConverter.convertToString(lineType.value())); 
                                                                                                            
        auto pen = QPen(qlineColor, qlineWidth, qlineType);
        auto fillColor = attributes.getHexFillColor();
        auto color = QColor((fillColor.has_value()) ? fillColor.value() : Qt::transparent);
        auto brush = QBrush(color); 
        //TODO: make a way to remove the fill color or the line color after it has been set
        painter.setPen(pen);
        painter.setBrush(brush);
    }


    QRect ShapeBase::getInnerTextRect(Formatting::DimentionConverter& converter, double margin)
    {
        auto geometry = item->getGeometry();

        auto coordinates = geometry.getPosition().value().getCoordinates();
        auto width = geometry.getWidth().value();
        auto height = geometry.getHeight().value();

        auto newWidth = width * margin;
        auto newHeight = height * margin;

        auto x = coordinates[0] + double(width - newWidth)/2;
        auto y = coordinates[1] + double(height - newHeight)/2;

        return QRect(converter.toPixels(x), converter.toPixels(y), 
                    converter.toPixels(newWidth), converter.toPixels(newHeight));
    }


    QRect ShapeBase::getRect(Formatting::DimentionConverter& converter) 
    {
        auto geometry = item->getGeometry();

        auto coordinates = geometry.getPosition().value().getCoordinates();
        auto height = geometry.getHeight().value();
        auto width = geometry.getWidth().value();
        QRect rect(converter.toPixels(coordinates[0]), converter.toPixels(coordinates[1]), 
            converter.toPixels(width), converter.toPixels(height));
        return rect;
    }




   
 

}

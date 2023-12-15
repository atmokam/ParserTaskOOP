#include <vector>
#include <QPainter>
#include <QtGui>
#include "ShapeBase.hpp"
#include "Data/ItemBase.hpp"
#include "Data/ItemAttributes.hpp"
#include "Serialization/Converter.hpp"
#include "Formatting/DimentionConverter.hpp"


ShapeBase::ShapeBase(std::shared_ptr<ItemBase> item) : item(item) {}

void ShapeBase::print(std::ostream& stream) 
{
    recursivePrintHandler(stream, item);
}

void ShapeBase::recursivePrintHandler(std::ostream& stream, const std::shared_ptr<ItemBase>& item) 
{
    if(auto leaf = std::dynamic_pointer_cast<ItemLeaf>(item))  
    {
        leafPrintHandler(stream, leaf);
    }
    else if(auto group = std::dynamic_pointer_cast<ItemGroup>(item))
    {
        for(auto& [_, subItem]: *group)
        {
            recursivePrintHandler(stream, subItem);
        }
    }

} 

void ShapeBase::leafPrintHandler(std::ostream& stream, const std::shared_ptr<ItemLeaf>& leaf) 
{
    Converter converter;
    stream << "Shape: " << converter.convertToString(leaf->getType()) << std::endl;
    stream << "---Geometry---" << std::endl;
    stream << "Position: " << converter.convertToString(leaf->getGeometry().getPosition().value()) << std::endl;
    stream << "Height: " << leaf->getGeometry().getHeight().value() << std::endl;
    stream << "Width: "<< leaf->getGeometry().getWidth().value() << std::endl;
    stream << "---Attributes---" << std::endl;
    stream << "FillColor: " << leaf->getAttributes().getHexFillColor().value() << std::endl;
    stream << "LineColor: " << leaf->getAttributes().getHexLineColor().value() << std::endl;
    stream << "LineWidth: " << leaf->getAttributes().getLineWidth().value() << std::endl;
    stream << "LineType: " << converter.convertToString(leaf->getAttributes().getLineType().value()) << std::endl;
}

std::shared_ptr<IShape> ShapeBase::clone(std::shared_ptr<ItemBase> item)
{
    setItem(item);
    return std::make_shared<ShapeBase>(*this);
}

void ShapeBase::setItem(std::shared_ptr<ItemBase> item)
{
    this->item = item;
}



// visual displayables

ShapeRectangle::ShapeRectangle(std::shared_ptr<ItemBase> item) : ShapeBase(item) {}

void ShapeRectangle::draw(QPainter& painter, DimentionConverter& converter) 
{
    auto position = item->getGeometry().getPosition();
    auto height = item->getGeometry().getHeight();
    auto width = item->getGeometry().getWidth();
    auto fillColor = item->getAttributes().getHexFillColor();
    auto lineColor = item->getAttributes().getHexLineColor();
    auto lineWidth = item->getAttributes().getLineWidth();
    auto lineType = item->getAttributes().getLineType();

    QColor lineColorValue = lineColor.value();
    qreal lineWidthValue = lineWidth.value();
    Qt::PenStyle lineTypeValue = Qt::PenStyle(Qt::PenStyle::DotLine);

    auto pen = QPen(lineColorValue, lineWidthValue, lineTypeValue);
    auto brush = QBrush(QColor(fillColor.value()));
    painter.setPen(pen);
    painter.setBrush(brush);
    std::vector<double> coordinates = position.value().getCoordinates();

    QRect rect(converter.toPixels(coordinates[0]), converter.toPixels(coordinates[1]), converter.toPixels(width.value()), converter.toPixels(height.value()));
    painter.drawRect(rect);
}


std::shared_ptr<IShape> ShapeRectangle::clone(std::shared_ptr<ItemBase> item)
{
    setItem(item);
    return std::make_shared<ShapeRectangle>(*this);
}


ShapeEllipse::ShapeEllipse(std::shared_ptr<ItemBase> item) : ShapeBase(item) {}

void ShapeEllipse::draw(QPainter& painter, DimentionConverter& converter) 
{
    
}

std::shared_ptr<IShape> ShapeEllipse::clone(std::shared_ptr<ItemBase> item)
{
    setItem(item);
    return std::make_shared<ShapeEllipse>(*this);
}


ShapeLine::ShapeLine(std::shared_ptr<ItemBase> item) : ShapeBase(item) {}

void ShapeLine::draw(QPainter& painter, DimentionConverter& converter) 
{
    
}


std::shared_ptr<IShape> ShapeLine::clone(std::shared_ptr<ItemBase> item)
{
    setItem(item);
    return std::make_shared<ShapeLine>(*this);
}


ShapeTrapezoid::ShapeTrapezoid(std::shared_ptr<ItemBase> item) : ShapeBase(item) {}

void ShapeTrapezoid::draw(QPainter& painter, DimentionConverter& converter) 
{
    
}

std::shared_ptr<IShape> ShapeTrapezoid::clone(std::shared_ptr<ItemBase> item)
{
    setItem(item);
    return std::make_shared<ShapeTrapezoid>(*this);
}


ShapeTriangle::ShapeTriangle(std::shared_ptr<ItemBase> item) : ShapeBase(item) {}

void ShapeTriangle::draw(QPainter& painter, DimentionConverter& converter) 
{
    
}

std::shared_ptr<IShape> ShapeTriangle::clone(std::shared_ptr<ItemBase> item)
{
    setItem(item);
    return std::make_shared<ShapeTriangle>(*this);
}


ShapeGroup::ShapeGroup(std::shared_ptr<ItemBase> item) : ShapeBase(item) {}

void ShapeGroup::draw(QPainter& painter, DimentionConverter& converter) 
{
    
}

std::shared_ptr<IShape> ShapeGroup::clone(std::shared_ptr<ItemBase> item)
{
    setItem(item);
    return std::make_shared<ShapeGroup>(*this);
}



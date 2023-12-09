#include "ShapeBase.hpp"
#include "Data/ItemBase.hpp"
#include "Data/ItemAttributes.hpp"
#include <vector>

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
    stream << "Shape: ";
    stream << leaf->getType() << std::endl;
    stream << "---Geometry---" << std::endl;
    stream << "Position: ";
    stream << leaf->getGeometry().getPosition().value() << std::endl;
    stream << "Height: ";
    stream << leaf->getGeometry().getHeight().value() << std::endl;
    stream << "Width: ";
    stream << leaf->getGeometry().getWidth().value() << std::endl;
    stream << "---Attributes---" << std::endl;
    stream << "FillColor: ";
    stream << leaf->getAttributes().getHexFillColor().value() << std::endl;
    stream << "LineColor: ";
    stream << leaf->getAttributes().getHexLineColor().value() << std::endl;
    stream << "LineWidth: ";
    stream << leaf->getAttributes().getLineWidth().value() << std::endl;
    stream << "LineType: ";
    stream << leaf->getAttributes().getLineType().value() << std::endl;
}

std::shared_ptr<IShape> ShapeBase::clone() const
{
    return std::make_shared<ShapeBase>(*this);
}


ShapeRectangle::ShapeRectangle(std::shared_ptr<ItemBase> item) : ShapeBase(item) {}

void ShapeRectangle::draw(QPainter& painter, DimentionConverter& converter) 
{
    
}

std::shared_ptr<IShape> ShapeRectangle::clone() const
{
    return std::make_shared<ShapeRectangle>(*this);
}


ShapeEllipse::ShapeEllipse(std::shared_ptr<ItemBase> item) : ShapeBase(item) {}

void ShapeEllipse::draw(QPainter& painter, DimentionConverter& converter) 
{
    
}

std::shared_ptr<IShape> ShapeEllipse::clone() const
{
    return std::make_shared<ShapeEllipse>(*this);
}


ShapeLine::ShapeLine(std::shared_ptr<ItemBase> item) : ShapeBase(item) {}

void ShapeLine::draw(QPainter& painter, DimentionConverter& converter) 
{
    
}


std::shared_ptr<IShape> ShapeLine::clone() const
{
    return std::make_shared<ShapeLine>(*this);
}


ShapeTrapezoid::ShapeTrapezoid(std::shared_ptr<ItemBase> item) : ShapeBase(item) {}

void ShapeTrapezoid::draw(QPainter& painter, DimentionConverter& converter) 
{
    
}

std::shared_ptr<IShape> ShapeTrapezoid::clone() const
{
    return std::make_shared<ShapeTrapezoid>(*this);
}


ShapeTriangle::ShapeTriangle(std::shared_ptr<ItemBase> item) : ShapeBase(item) {}

void ShapeTriangle::draw(QPainter& painter, DimentionConverter& converter) 
{
    
}

std::shared_ptr<IShape> ShapeTriangle::clone() const
{
    return std::make_shared<ShapeTriangle>(*this);
}


ShapeGroup::ShapeGroup(std::shared_ptr<ItemBase> item) : ShapeBase(item) {}

void ShapeGroup::draw(QPainter& painter, DimentionConverter& converter) 
{
    
}

std::shared_ptr<IShape> ShapeGroup::clone() const
{
    return std::make_shared<ShapeGroup>(*this);
}



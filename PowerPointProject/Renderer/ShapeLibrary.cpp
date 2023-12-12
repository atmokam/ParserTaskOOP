#include "ShapeLibrary.hpp"
#include "IShape.hpp"
#include "ShapeBase.hpp"
#include "ItemBase.hpp"

ShapeLibrary::ShapeLibrary() 
{
    library[Type::Rectangle] = std::make_shared<ShapeRectangle>(nullptr);
    library[Type::Trapezoid] = std::make_shared<ShapeTrapezoid>(nullptr);
    library[Type::Ellipse] = std::make_shared<ShapeEllipse>(nullptr);
    library[Type::Line] = std::make_shared<ShapeLine>(nullptr);
    library[Type::Triangle] = std::make_shared<ShapeTriangle>(nullptr);
    library[Type::Group] = std::make_shared<ShapeGroup>(nullptr);
}

std::shared_ptr<IShape> ShapeLibrary::getShape(std::shared_ptr<ItemBase> item)
{
    return library[item->getType()]->clone(item);
}
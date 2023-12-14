#include "ShapeLibrary.hpp"
#include "IShape.hpp"
#include "ShapeBase.hpp"
#include "Data/ItemBase.hpp"

ShapeLibrary::ShapeLibrary() 
{
    library[Type::Rectangle] = std::make_shared<ShapeRectangle>(nullptr);
    library[Type::Trapezoid] = std::make_shared<ShapeTrapezoid>(nullptr);
    library[Type::Ellipse] = std::make_shared<ShapeEllipse>(nullptr);
    library[Type::Line] = std::make_shared<ShapeLine>(nullptr);
    library[Type::Triangle] = std::make_shared<ShapeTriangle>(nullptr);
    library[Type::Group] = std::make_shared<ShapeGroup>(nullptr);

    stringToType["rectangle"] = Type::Rectangle;
    stringToType["trapezoid"] = Type::Trapezoid;
    stringToType["ellipse"] = Type::Ellipse;
    stringToType["line"] = Type::Line;
    stringToType["triangle"] = Type::Triangle;
    stringToType["group"] = Type::Group;
}

std::shared_ptr<IShape> ShapeLibrary::getShape(std::shared_ptr<ItemBase> item)
{
    return library[item->getType()]->clone(item);
}

std::optional<Type> ShapeLibrary::getType(const std::string& type)
{
    return (stringToType.find(type) != stringToType.end()) ? std::optional<Type>(stringToType[type]) : std::nullopt;
}
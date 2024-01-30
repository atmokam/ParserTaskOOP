#include "ShapeLibrary.hpp"
#include "ICloneable.hpp"
#include "ShapeBase.hpp"
#include "Data/Item/ItemBase.hpp"
#include "ShapeText.hpp"

namespace Renderer
{
    ShapeLibrary::ShapeLibrary() 
    {
        library[Type::Rectangle] = std::make_shared<ShapeRectangle>(nullptr);
        library[Type::Trapezoid] = std::make_shared<ShapeTrapezoid>(nullptr);
        library[Type::Ellipse] = std::make_shared<ShapeEllipse>(nullptr);
        library[Type::Line] = std::make_shared<ShapeLine>(nullptr);
        library[Type::Triangle] = std::make_shared<ShapeTriangle>(nullptr);

        stringToType["rectangle"] = Type::Rectangle;
        stringToType["trapezoid"] = Type::Trapezoid;
        stringToType["ellipse"] = Type::Ellipse;
        stringToType["line"] = Type::Line;
        stringToType["triangle"] = Type::Triangle;
    }

    std::shared_ptr<ICloneable> ShapeLibrary::getShape(std::shared_ptr<Data::ItemBase> item)
    {
        auto shape = library[item->getType()]->clone(item);
        auto textWrapped = ShapeText(std::dynamic_pointer_cast<ShapeBase>(shape));
        return std::make_shared<ShapeText>(textWrapped);
    }

    Type ShapeLibrary::getType(const std::string& type)
    {
        return (stringToType.find(type) != stringToType.end()) ? stringToType[type] : Type::None;
    }

    std::string ShapeLibrary::getString(const Type type)
    {
        switch(type)
        {
            case Type::Rectangle:
                return "rectangle";
            case Type::Ellipse:
                return "ellipse";
            case Type::Line:
                return "line";
            case Type::Trapezoid:
                return "trapezoid";
            case Type::Triangle:
                return "triangle";
            default:
                return "";
        }
    }
}
#ifndef SHAPELIBRARY_HPP
#define SHAPELIBRARY_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include <optional>

#include "Data/ItemBase.hpp"

namespace Renderer
{
    class IShape;

    enum class Type 
    {
        Rectangle, Trapezoid, Ellipse, Line, Triangle, Group
    };


    class ShapeLibrary {
        std::unordered_map<Type, std::shared_ptr<IShape>> library;
        std::unordered_map<std::string, Type> stringToType;
    public:
        ShapeLibrary();
        std::shared_ptr<IShape> getShape(std::shared_ptr<Data::ItemBase> item);
        
        std::optional<Type> getType(const std::string& type);
        std::string getString(const Type type);

    };
}
#endif
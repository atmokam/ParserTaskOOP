#ifndef SHAPELIBRARY_HPP
#define SHAPELIBRARY_HPP

#include <string>
#include <unordered_map>
#include <memory>

#include "Data/Item/ItemBase.hpp"


//                                      Intent: prototype library for shapes


namespace Renderer
{
    class ICloneable;

    enum class Type 
    {
        Rectangle, Trapezoid, Ellipse, Line, Triangle, Group, None
    };


    class ShapeLibrary {
        std::unordered_map<Type, std::shared_ptr<ICloneable>> library;
        std::unordered_map<std::string, Type> stringToType;
    public:
        ShapeLibrary();
        std::shared_ptr<ICloneable> getShape(std::shared_ptr<Data::ItemBase> item);
        
        Type getType(const std::string& type);
        std::string getString(const Type type);

    };
}
#endif
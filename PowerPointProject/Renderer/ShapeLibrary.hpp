#ifndef SHAPELIBRARY_HPP
#define SHAPELIBRARY_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>

class IShape;
class ShapeBase;
class ItemBase;

enum class Type 
{
    Rectangle, Trapezoid, Ellipse, Line, Triangle, Group
};


class ShapeLibrary {
    std::unordered_map<Type, std::shared_ptr<IShape>> library;
public:
    ShapeLibrary();
    std::shared_ptr<IShape> getShape(std::shared_ptr<ItemBase> item);

};

#endif
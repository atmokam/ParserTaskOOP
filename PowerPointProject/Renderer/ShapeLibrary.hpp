#ifndef SHAPELIBRARY_HPP
#define SHAPELIBRARY_HPP

#include <string>
#include <unordered_map>

#include "IShape.hpp"
#include "ShapeBase.hpp"

class ShapeLibrary {
    std::unordered_map<std::string, std::shared_ptr<IShape>> library;
public:
    ShapeLibrary();
    std::shared_ptr<IShape> getShape(std::string name);
};

#endif
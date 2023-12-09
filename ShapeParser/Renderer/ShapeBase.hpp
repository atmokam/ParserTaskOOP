#ifndef SHAPEBASE_HPP
#define SHAPEBASE_HPP

#include <memory>

#include "IVisualDisplayable.hpp"
#include "IShape.hpp"

class ItemBase;
class QPainter;
class DimentionConverter;

class ShapeBase : public IShape {
    std::shared_ptr<ItemBase> item;
    void recursivePrintHandler(std::ostream& stream, const std::shared_ptr<ItemBase>& item);
    void leafPrintHandler(std::ostream& stream, const std::shared_ptr<ItemLeaf>& leaf);
public:
    void print(std::ostream& stream) override;
    ShapeBase(std::shared_ptr<ItemBase> item);
};

class ShapeRectangle : public ShapeBase, public IVisualDisplayable {  
public:
    ShapeRectangle(std::shared_ptr<ItemBase> item);
    void draw(QPainter& painter, DimentionConverter& converter) override;
};

class ShapeEllipse : public ShapeBase, public IVisualDisplayable {
public:
    ShapeEllipse(std::shared_ptr<ItemBase> item);
    void draw(QPainter& painter, DimentionConverter& converter) override;

};

class ShapeLine : public ShapeBase, public IVisualDisplayable {
public:
    ShapeLine(std::shared_ptr<ItemBase> item);
    void draw(QPainter& painter, DimentionConverter& converter) override;

};

class ShapeTrapezoid : public ShapeBase, public IVisualDisplayable {
public:
    ShapeTrapezoid(std::shared_ptr<ItemBase> item);
    void draw(QPainter& painter, DimentionConverter& converter) override;

};

class ShapeTriangle : public ShapeBase, public IVisualDisplayable {
public:
    ShapeTriangle(std::shared_ptr<ItemBase> item);
    void draw(QPainter& painter, DimentionConverter& converter) override;

};

#endif
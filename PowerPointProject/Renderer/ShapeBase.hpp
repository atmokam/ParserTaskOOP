#ifndef SHAPEBASE_HPP
#define SHAPEBASE_HPP

#include <memory>

#include "IVisualDisplayable.hpp"
#include "ITextDisplayable.hpp"
#include "IShape.hpp"

class ItemBase;
class QPainter;
class DimentionConverter;

class ShapeBase : public IShape, public ITextDisplayable    
{                                                           
    std::shared_ptr<ItemBase> item;
    void recursivePrintHandler(std::ostream& stream, const std::shared_ptr<ItemBase>& item);
    void leafPrintHandler(std::ostream& stream, const std::shared_ptr<ItemLeaf>& leaf);
public:
    void print(std::ostream& stream) override;
    ShapeBase(std::shared_ptr<ItemBase> item);
    virtual std::shared_ptr<IShape> clone() const;
};

class ShapeRectangle : public ShapeBase, public IVisualDisplayable {  
public:
    ShapeRectangle(std::shared_ptr<ItemBase> item);
    void draw(QPainter& painter, DimentionConverter& converter) override;
    std::shared_ptr<IShape> clone() const override;
};

class ShapeEllipse : public ShapeBase, public IVisualDisplayable {
public:
    ShapeEllipse(std::shared_ptr<ItemBase> item);
    void draw(QPainter& painter, DimentionConverter& converter) override;
    std::shared_ptr<IShape> clone() const override;

};

class ShapeLine : public ShapeBase, public IVisualDisplayable {
public:
    ShapeLine(std::shared_ptr<ItemBase> item);
    void draw(QPainter& painter, DimentionConverter& converter) override;
    std::shared_ptr<IShape> clone() const override;

};

class ShapeTrapezoid : public ShapeBase, public IVisualDisplayable {
public:
    ShapeTrapezoid(std::shared_ptr<ItemBase> item);
    void draw(QPainter& painter, DimentionConverter& converter) override;
    std::shared_ptr<IShape> clone() const override;

};

class ShapeTriangle : public ShapeBase, public IVisualDisplayable {
public:
    ShapeTriangle(std::shared_ptr<ItemBase> item);
    void draw(QPainter& painter, DimentionConverter& converter) override;
    std::shared_ptr<IShape> clone() const override;

};

class ShapeGroup : public ShapeBase, public IVisualDisplayable { 
public:
    ShapeGroup(std::shared_ptr<ItemBase> item);
    void draw(QPainter& painter, DimentionConverter& converter) override;
    std::shared_ptr<IShape> clone() const override;

};

#endif
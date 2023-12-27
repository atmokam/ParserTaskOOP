#ifndef SHAPEBASE_HPP
#define SHAPEBASE_HPP

// intent: rendered entity

#include <memory>

#include "IVisualDisplayable.hpp"
#include "ITextDisplayable.hpp"
#include "IShape.hpp"
#include "Data/ItemBase.hpp"


class QPainter;
class QRect;

namespace Renderer
{
    namespace Formatting
    {
        class DimentionConverter;
    }

    class ShapeBase : public IShape, public ITextDisplayable
    {   
    protected:                                                        
        std::shared_ptr<Data::ItemBase> item;

        void setPainterAttributes(QPainter& painter);
        QRect getRect(Formatting::DimentionConverter& converter);//
    public:
        void print(std::ostream& stream) override;
        ShapeBase(std::shared_ptr<Data::ItemBase> item);
        void setItem(std::shared_ptr<Data::ItemBase> item);
        std::shared_ptr<Data::ItemBase> getItem() const;
        virtual std::shared_ptr<IShape> clone(std::shared_ptr<Data::ItemBase> item) override;
        virtual void accept(IShapeVisitor& visitor) override {}
    };



    class ShapeRectangle : public ShapeBase, public IVisualDisplayable {  
    public:
        ShapeRectangle(std::shared_ptr<Data::ItemBase> item);
        void draw(QPainter& painter, Formatting::DimentionConverter& converter) override;
        std::shared_ptr<IShape> clone(std::shared_ptr<Data::ItemBase> item) override;
        void accept(IShapeVisitor& visitor) override;
    };

    class ShapeEllipse : public ShapeBase, public IVisualDisplayable {
    public:
        ShapeEllipse(std::shared_ptr<Data::ItemBase> item);
        void draw(QPainter& painter, Formatting::DimentionConverter& converter) override;
        std::shared_ptr<IShape> clone(std::shared_ptr<Data::ItemBase> item) override;
        void accept(IShapeVisitor& visitor) override;

    };

    class ShapeLine : public ShapeBase, public IVisualDisplayable {
    public:
        ShapeLine(std::shared_ptr<Data::ItemBase> item);
        void draw(QPainter& painter, Formatting::DimentionConverter& converter) override;
        std::shared_ptr<IShape> clone(std::shared_ptr<Data::ItemBase> item) override;
        void accept(IShapeVisitor& visitor) override;


    };

    class ShapeTrapezoid : public ShapeBase, public IVisualDisplayable {
    public:
        ShapeTrapezoid(std::shared_ptr<Data::ItemBase> item);
        void draw(QPainter& painter, Formatting::DimentionConverter& converter) override;
        std::shared_ptr<IShape> clone(std::shared_ptr<Data::ItemBase> item) override;
        void accept(IShapeVisitor& visitor) override;

    };

    class ShapeTriangle : public ShapeBase, public IVisualDisplayable {
    public:
        ShapeTriangle(std::shared_ptr<Data::ItemBase> item);
        void draw(QPainter& painter, Formatting::DimentionConverter& converter) override;
        std::shared_ptr<IShape> clone(std::shared_ptr<Data::ItemBase> item) override;
        void accept(IShapeVisitor& visitor) override;

    };
}


#endif
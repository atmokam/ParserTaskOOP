#ifndef SHAPEBASE_HPP
#define SHAPEBASE_HPP

#include <memory>

#include "IVisualDisplayable.hpp"
#include "ITextDisplayable.hpp"
#include "ICloneable.hpp"
#include "Data/Item/ItemBase.hpp"

// fwd declarations
class QPainter;
class QRect;

namespace Renderer
{
    namespace Formatting
    {
        class DimentionConverter;
    }


    //                             Intent: this class does the entire rendering of shape

    class ShapeBase : public ICloneable, public ITextDisplayable
    {   
    protected:     

        std::shared_ptr<Data::ItemBase> item;

        void setPainterAttributes(QPainter& painter);
        QRect getInnerTextRect(Formatting::DimentionConverter& converter, double margin);
        QRect getRect(Formatting::DimentionConverter& converter);

    public:

        ShapeBase(std::shared_ptr<Data::ItemBase> item);
        void setItem(std::shared_ptr<Data::ItemBase> item);
        std::shared_ptr<Data::ItemBase> getItem() const;

        void print(std::ostream& stream) override;
        
        virtual std::shared_ptr<ICloneable> clone(std::shared_ptr<Data::ItemBase> item) override;
        
    };



    class ShapeRectangle : public ShapeBase, public IVisualDisplayable 
    {  
    public:
        ShapeRectangle(std::shared_ptr<Data::ItemBase> item);
        void draw(QPainter& painter, Formatting::DimentionConverter& converter) override;
        std::shared_ptr<ICloneable> clone(std::shared_ptr<Data::ItemBase> item) override;
        
    };

    class ShapeEllipse : public ShapeBase, public IVisualDisplayable 
    {
    public:
        ShapeEllipse(std::shared_ptr<Data::ItemBase> item);
        void draw(QPainter& painter, Formatting::DimentionConverter& converter) override;
        std::shared_ptr<ICloneable> clone(std::shared_ptr<Data::ItemBase> item) override;
        

    };

    class ShapeLine : public ShapeBase, public IVisualDisplayable 
    {
    public:
        ShapeLine(std::shared_ptr<Data::ItemBase> item);
        void draw(QPainter& painter, Formatting::DimentionConverter& converter) override;
        std::shared_ptr<ICloneable> clone(std::shared_ptr<Data::ItemBase> item) override;
        
    };

    class ShapeTrapezoid : public ShapeBase, public IVisualDisplayable 
    {
    public:
        ShapeTrapezoid(std::shared_ptr<Data::ItemBase> item);
        void draw(QPainter& painter, Formatting::DimentionConverter& converter) override;
        std::shared_ptr<ICloneable> clone(std::shared_ptr<Data::ItemBase> item) override;
        

    };

    class ShapeTriangle : public ShapeBase, public IVisualDisplayable 
    {

    public:
        ShapeTriangle(std::shared_ptr<Data::ItemBase> item);
        void draw(QPainter& painter, Formatting::DimentionConverter& converter) override;
        std::shared_ptr<ICloneable> clone(std::shared_ptr<Data::ItemBase> item) override;
        

    };
}


#endif
#ifndef ISHAPE_HPP
#define ISHAPE_HPP

#include <memory>

namespace Data
{
    class ItemBase;
}

namespace Renderer
{
    class IShapeVisitor;
    
    class IShape 
    {
    public:
        virtual std::shared_ptr<IShape> clone(std::shared_ptr<Data::ItemBase> item) = 0;
        virtual void accept(std::weak_ptr<IShapeVisitor> visitor) = 0;
    }; 
}


#endif
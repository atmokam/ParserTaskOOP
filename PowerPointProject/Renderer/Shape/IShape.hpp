#ifndef ISHAPE_HPP
#define ISHAPE_HPP

#include <memory>
#include "Data/ItemBase.hpp"
#include "IShapeVisitor.hpp"

namespace Renderer
{

    class IShape {
    public:
        virtual std::shared_ptr<IShape> clone(std::shared_ptr<Data::ItemBase> item) = 0;
        virtual void accept(IShapeVisitor& visitor) = 0;
    }; 
}


#endif
#ifndef ICLONEABLE_HPP
#define ICLONEABLE_HPP

#include <memory>

namespace Data
{
    class ItemBase;
}

namespace Renderer
{
    class ICloneable 
    {
    public:
        virtual std::shared_ptr<ICloneable> clone(std::shared_ptr<Data::ItemBase> item) = 0;
    }; 
}


#endif
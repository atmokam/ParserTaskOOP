#ifndef IVISITOR_HPP
#define IVISITOR_HPP

#include <memory>

namespace Data
{
    class ItemGroup;
    class ItemLeaf;
   

    class IVisitor
    {
    public:
        virtual void visit(ItemLeaf& item) = 0;
        virtual void visit(ItemGroup& item) = 0;
    };
}

#endif
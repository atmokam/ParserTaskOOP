#ifndef IITEMVISITOR_HPP
#define IITEMVISITOR_HPP

#include <memory>

namespace Data
{
    class ItemGroup;
    class ItemLeaf;
   

    class IItemVisitor
    {
    public:
        virtual void visit(ItemLeaf& item) = 0;
        virtual void visit(ItemGroup& item) = 0;
    };
}

#endif
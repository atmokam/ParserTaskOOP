#ifndef VISUALRENDERINGVISITOR_HPP
#define VISUALRENDERINGVISITOR_HPP

#include "Data/IVisitor.hpp"
#include <memory>

namespace Renderer
{
    class VisualRenderingVisitor: public Data::IVisitor
    {
    public:
        virtual void visit(Data::ItemLeaf& item) override;
        virtual void visit(Data::ItemGroup& item) override;
    };
}

#endif
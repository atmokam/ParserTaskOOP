#ifndef CONSOLERENDERINGVISITOR_HPP
#define CONSOLERENDERINGVISITOR_HPP

#include <string>
#include <sstream>

#include "Include/IItemVisitor.hpp"

namespace Data
{
    class ItemBase;
    class ItemLeaf;
    class ItemGroup;
    class Slide;
}

namespace Renderer
{
    class ConsoleRenderingVisitor : public Data::IItemVisitor
    {
        std::reference_wrapper<std::ostream> output;
    public:
        ConsoleRenderingVisitor(std::ostream& output);
        void visit(Data::ItemLeaf& item) override;
        void visit(Data::ItemGroup& item) override;
        void print(const std::shared_ptr<Data::Slide>& slide);
        void print(const std::shared_ptr<Data::ItemBase>& item);
    };

}
#endif
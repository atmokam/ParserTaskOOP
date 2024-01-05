#include "ConsoleRenderingVisitor.hpp"
#include "Data/Slide.hpp"
#include "Data/Item/ItemBase.hpp"
#include "Renderer/Shape/ShapeBase.hpp"

namespace Renderer
{
    ConsoleRenderingVisitor::ConsoleRenderingVisitor(std::ostream& output) : output(output) {}

    void ConsoleRenderingVisitor::visit(Data::ItemLeaf& leaf)
    {
        ShapeBase shape(std::make_shared<Data::ItemLeaf>(leaf)); // is cloning better than this?
        shape.print(output);
    }

    void ConsoleRenderingVisitor::visit(Data::ItemGroup& item)
    {
        for(auto& [_, subItem]: item)
        {
            subItem->accept(std::make_shared<ConsoleRenderingVisitor>(*this));
        }
    }

    void ConsoleRenderingVisitor::print(const std::shared_ptr<Data::ItemBase>& item)
    {
        item->accept(std::make_shared<ConsoleRenderingVisitor>(*this));
    }

    void ConsoleRenderingVisitor::print(const std::shared_ptr<Data::Slide>& slide )
    {
        auto items = slide->getTopItem();
        items->accept(std::make_shared<ConsoleRenderingVisitor>(*this));
    }
}

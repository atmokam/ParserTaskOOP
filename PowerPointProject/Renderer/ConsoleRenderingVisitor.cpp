#include "ConsoleRenderingVisitor.hpp"
#include "Data/Slide.hpp"
#include "Data/Item/ItemBase.hpp"
#include "Renderer/Shape/ShapeBase.hpp"
#include "Serialization/Converter.hpp"

namespace Renderer
{
    ConsoleRenderingVisitor::ConsoleRenderingVisitor(std::ostream& output) : output(output) {}

    void ConsoleRenderingVisitor::visit(Data::ItemLeaf& leaf)
    {
        ShapeBase shape(std::make_shared<Data::ItemLeaf>(leaf));
        shape.print(output.get());
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

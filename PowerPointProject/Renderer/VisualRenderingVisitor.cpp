#include "Renderer/VisualRenderingVisitor.hpp"
#include <QPainter>
#include <QPaintDevice>
#include <memory>
#include "Shape/ShapeLibrary.hpp"
#include "Application/Application.hpp"
#include "Data/IDGenerator.hpp"
#include "Shape/IShape.hpp"
#include "Shape/IVisualDisplayable.hpp"

namespace Renderer
{
    VisualRenderingVisitor::VisualRenderingVisitor(QPaintDevice& device, Formatting::DimentionConverter& converter)
        : device(device), converter(converter)
    {
        shapeLibrary = std::make_shared<ShapeLibrary>();
    }

    void VisualRenderingVisitor::visit(Data::ItemLeaf& item) // leaf accept
    {
        QPainter painter(&device);
        auto shape = shapeLibrary->getShape(std::make_shared<Data::ItemLeaf>(item));
        std::shared_ptr<IVisualDisplayable> visualShape = std::dynamic_pointer_cast<IVisualDisplayable>(shape);
        visualShape->draw(painter, converter);
    }

    void VisualRenderingVisitor::visit(Data::ItemGroup& items) // group accept
    {
        auto doc = App::Application::getInstance().getDocument(); 
        auto ids = doc->getIDGenerator().getIDs(); // TODO: add to itemgroup: sequence of added shapes
        for(const auto& id: ids)
        {
            auto item = items.getItem(id);
            if(item)
            {
                item->accept(std::make_shared<VisualRenderingVisitor>(*this));
            }
        }
    }

    void VisualRenderingVisitor::draw(const std::shared_ptr<Data::ItemBase>& item) // visit invoker
    {
        item->accept(std::make_shared<VisualRenderingVisitor>(*this));
    }

}


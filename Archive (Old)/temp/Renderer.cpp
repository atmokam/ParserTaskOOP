#include "Renderer.hpp"
#include <QPainter>
#include <QPaintDevice>
#include "Formatting/DimentionConverter.hpp"
#include "Data/Slide.hpp"
#include "Shape/ShapeLibrary.hpp" 
#include "Shape/IShape.hpp"
#include "Shape/IVisualDisplayable.hpp"
#include "Application/Application.hpp"
#include "Data/IDGenerator.hpp"

namespace Renderer
{

    Renderer::Renderer(std::unique_ptr<QPaintDevice> device, std::unique_ptr<Formatting::DimentionConverter> converter)
        : device(std::move(device)), converter(std::move(converter))
    {
        shapeLibrary = std::make_shared<ShapeLibrary>();
    }
/*
    void Renderer::draw(const std::shared_ptr<Data::Slide>& slide)
    { 
        QPainter painter(device.get());
        App::Application& app = *App::Application::getInstance();
        
        VisualRenderingVisitor visitor(painter, converter);
        auto ids = app.getDocument()->getIDGenerator().getIDs();
        auto items = slide->getTopItem();
        items->accept()

        // for (auto& id: ids) 
        // {
        //     auto item = slide->getItem(id);
        //     if(item)
        //     {
        //         auto shape = shapeLibrary.getShape(item);
        //         std::shared_ptr<IVisualDisplayable> visualShape = std::dynamic_pointer_cast<IVisualDisplayable>(shape);
        //         visualShape->draw(painter, converter);
        //     }
        // }

    }
    */
}
#include "Renderer.hpp"
#include <QPainter>
#include <QPaintDevice>
#include "Formatting/DimentionConverter.hpp"
#include "Data/Slide.hpp"
#include "ShapeLibrary.hpp" 
#include "IShape.hpp"
#include "IVisualDisplayable.hpp"
#include "Application/Application.hpp"
#include "Data/IDGenerator.hpp"

namespace Renderer
{

    void Renderer::draw(QPaintDevice& device, Formatting::DimentionConverter& converter, const std::shared_ptr<Data::Slide>& slide)
    {
        QPainter painter(&device);
        App::Application& app = *App::Application::getInstance();
        ShapeLibrary shapeLibrary;   // should this be created elsewhere?
        auto ids = app.getDocument()->getIDGenerator().getIDs();
        for (auto& id: ids) 
        {
            auto shape = shapeLibrary.getShape(slide->getItem(id));
            std::shared_ptr<IVisualDisplayable> visualShape = std::dynamic_pointer_cast<IVisualDisplayable>(shape);
            visualShape->draw(painter, converter);
        }

    }
}
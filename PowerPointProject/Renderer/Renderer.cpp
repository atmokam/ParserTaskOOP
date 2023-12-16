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



void Renderer::draw(QPaintDevice& device, DimentionConverter& converter, const std::shared_ptr<Slide>& slide)
{
    QPainter painter(&device);
    App::Application& app = App::Application::getInstance();
    ShapeLibrary shapeLibrary;   // should this be created elsewhere?
    auto ids = app.getDocument()->getIDGenerator().getIDs();
    for (auto& id: ids) // for sequental iteration, change this
    {
        auto shape = shapeLibrary.getShape(slide->getItem(id));
        std::shared_ptr<IVisualDisplayable> visualShape = std::dynamic_pointer_cast<IVisualDisplayable>(shape);
        visualShape->draw(painter, converter);
        
    }

}
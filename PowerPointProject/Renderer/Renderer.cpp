#include "Renderer.hpp"
#include <QPainter>
#include <QPaintDevice>
#include "Formatting/DimentionConverter.hpp"
#include "Data/Slide.hpp"
#include "ShapeLibrary.hpp" 
#include "IShape.hpp"
#include "IVisualDisplayable.hpp"
#include "Application/Application.hpp"



void Renderer::draw(QPaintDevice& device, DimentionConverter& converter, const std::shared_ptr<Slide>& slide)
{
    QPainter painter(&device);
    App::Application& app = App::Application::getInstance();
    ShapeLibrary shapeLibrary;   // should this be created elsewhere?
    size_t max = app.getDocument()->getMaximumID();
    for (size_t i = 0; i <= max; ++i) // for sequental iteration
    {
        auto shape = shapeLibrary.getShape(slide->getItem(i));
        std::shared_ptr<IVisualDisplayable> visualShape = std::dynamic_pointer_cast<IVisualDisplayable>(shape);
        visualShape->draw(painter, converter);
        
    }

}
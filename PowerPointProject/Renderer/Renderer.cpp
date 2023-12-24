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

    void Renderer::draw(const std::shared_ptr<Data::Slide>& slide)
    { ///////////
        QPainter painter(device);
        App::Application& app = *App::Application::getInstance();
        
        auto ids = app.getDocument()->getIDGenerator().getIDs();
        for (auto& id: ids) 
        {
            auto item = slide->getItem(id);
            if(item)
            {
                auto shape = shapeLibrary.getShape(item);
                std::shared_ptr<IVisualDisplayable> visualShape = std::dynamic_pointer_cast<IVisualDisplayable>(shape);
                visualShape->draw(painter, converter);
            }
        }

    }
}
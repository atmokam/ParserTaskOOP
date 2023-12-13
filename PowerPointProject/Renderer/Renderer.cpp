#include "Renderer.hpp"
#include <QPainter>
#include <QPaintDevice>
#include "Formatting/DimentionConverter.hpp"
#include "Data/Slide.hpp"
#include "ShapeLibrary.hpp" 
#include "IShape.hpp"
#include "IVisualDisplayable.hpp"



void Renderer::draw(QPaintDevice& device, DimentionConverter& converter, const std::shared_ptr<Slide>& slide)
{
    QPainter painter(&device);

    ShapeLibrary shapeLibrary;   // should this be created elsewhere?
    for (auto& item : *slide)
    {
        auto shape = shapeLibrary.getShape(item.second);
        std::shared_ptr<IVisualDisplayable> visualShape = std::dynamic_pointer_cast<IVisualDisplayable>(shape);
        visualShape->draw(painter, converter);
        
    }

}
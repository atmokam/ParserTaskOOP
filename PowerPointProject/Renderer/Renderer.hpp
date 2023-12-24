#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>

#include "Data/Slide.hpp"
#include "Shape/ShapeLibrary.hpp"
#include "Formatting/DimentionConverter.hpp"
#include <QPaintDevice>



namespace Renderer // is it a good practice to name the class and the namespace the same way?
{
    class Renderer
    {
        std::shared_ptr<ShapeLibrary> shapeLibrary;    
        std::unique_ptr<QPaintDevice> device;
        std::unique_ptr<Formatting::DimentionConverter> converter;
    public:
        void draw(const std::shared_ptr<Data::Slide>& slide);
        void draw(const std::shared_ptr<Data::ItemBase>& item);
    };
}
#endif
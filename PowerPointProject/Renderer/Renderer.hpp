#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>

#include "Data/Slide.hpp"
class QPaintDevice;


namespace Renderer // is it a good practice to name the class and the namespace the same way?
{
    namespace Formatting
    {
        class DimentionConverter;
    }
    
    class Renderer
    {
    public:
        void draw(QPaintDevice& device, Formatting::DimentionConverter& converter, const std::shared_ptr<Data::Slide>& slide);
    };
}
#endif
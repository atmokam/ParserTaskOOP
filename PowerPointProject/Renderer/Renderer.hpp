#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>

class QPaintDevice;
class DimentionConverter;
class Slide;

class Renderer
{
public:
    void draw(QPaintDevice& device, DimentionConverter& converter, const std::shared_ptr<Slide>& slide);
};

#endif
#ifndef RENDERER_HPP
#define RENDERER_HPP

class QPaintDevice;
class DimentionConverter;

class Renderer
{
public:
    void draw(QPaintDevice& device, DimentionConverter& converter, const std::shared_ptr<Slide>& slide);
};

#endif
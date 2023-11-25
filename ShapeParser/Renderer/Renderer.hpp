#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>

#include "IRenderer.hpp"
#include "Data/ItemAttributes.hpp"

class Renderer : public IRenderer {
    void lineDescriptorToText(std::ostream& os, const LineDescriptor line);
    void shapeToText(std::ostream& os, const ShapeType& shape) ;
    void positionToText(std::ostream& os, const Position& position);
    void boundingRectToText(std::ostream& os, const BoundingRect& rect);
    void colorToText(std::ostream& os, const Color& color);
public:
    void renderText(std::ostream& os, const std::shared_ptr<Slide>& slide, const size_t slideNumber) override;
    void renderText(std::ostream& os, const std::shared_ptr<Document>& slide) override;
    void renderImage(std::shared_ptr<Slide>& slide) override;
    void renderText(std::ostream& os, const std::shared_ptr<Item>& item) override;
    void renderImage(std::shared_ptr<Item>& item) override;
};



#endif
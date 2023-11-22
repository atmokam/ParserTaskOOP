#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>

#include "Interfaces/IRenderer.hpp"
#include "Data/ItemAttributes.hpp"

class Renderer : public IRenderer {
public:
    void renderText(std::ostream& os, const std::shared_ptr<Slide>& slide) override;
    void renderText(std::ostream& os, const std::shared_ptr<Document>& slide) override;
    void renderImage(std::shared_ptr<Slide>& slide) override;
    void renderText(std::ostream& os, const std::shared_ptr<Item>& item) override;
    void renderImage(std::shared_ptr<Item>& item) override;
};



#endif
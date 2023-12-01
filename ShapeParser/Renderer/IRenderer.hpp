#ifndef IRENDERER_HPP
#define IRENDERER_HPP

#include <memory>
#include <ostream>

class Slide;
class Document;
class Item;

class IRenderer {
public:
    virtual void renderText(std::ostream& os, const std::shared_ptr<Slide>& slide, const size_t slideNumber) = 0;
    virtual void renderText(std::ostream& os, const std::shared_ptr<Document>& slide) = 0;
    virtual void renderImage(std::shared_ptr<Slide>& slide) = 0;
    virtual void renderText(std::ostream& os, const std::shared_ptr<Item>& item) = 0;
    virtual void renderImage(std::shared_ptr<Item>& item) = 0;
};


#endif
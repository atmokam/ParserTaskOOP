#include "Document.hpp"

std::vector<std::shared_ptr<Slide>> Document::getAllSlides() const {
    return slides;
}

void Document::addSlide(std::shared_ptr<Slide> slide) {
    slides.push_back(slide);
}

std::shared_ptr<Slide> Document::getSlide(size_t current) const {
    return (!slides.empty()) ? slides.at(current) : nullptr;
}

Document::Document() {
    slides.push_back(std::make_shared<Slide>());
}


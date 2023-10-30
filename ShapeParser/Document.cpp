#include "Document.hpp"

std::vector<std::shared_ptr<Slide>> Document::getAllSlides() const {
    return slides;
}

void Document::addSlide(std::shared_ptr<Slide> slide) {
    slides.push_back(slide);
}

std::shared_ptr<Slide> Document::getSlide(size_t number) const {
    return (!slides.empty()) ? slides.at(number) : nullptr;
}

Document::Document() {
    slides.push_back(std::make_shared<Slide>());
}

std::vector<std::shared_ptr<Slide>>::iterator Document::begin() {
    return slides.begin();
}

std::vector<std::shared_ptr<Slide>>::const_iterator Document::cbegin() const {
    return slides.cbegin();
}

std::vector<std::shared_ptr<Slide>>::iterator Document::end() {
    return slides.end();
}

std::vector<std::shared_ptr<Slide>>::const_iterator Document::cend() const {
    return slides.cend();
}

std::vector<std::shared_ptr<Slide>>::reverse_iterator Document::rbegin() {
    return slides.rbegin();
}

std::vector<std::shared_ptr<Slide>>::const_reverse_iterator Document::crbegin() const {
    return slides.crbegin();
}

std::vector<std::shared_ptr<Slide>>::reverse_iterator Document::rend() {
    return slides.rend();
}

std::vector<std::shared_ptr<Slide>>::const_reverse_iterator Document::crend() const {
    return slides.crend();
}





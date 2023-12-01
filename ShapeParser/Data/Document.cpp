#include <algorithm>
#include "Document.hpp"
#include "Slide.hpp"


DocumentContainer Document::getAllSlides() const {
    return slides;
}

void Document::addSlide(std::shared_ptr<Slide> slide) {
    slides.push_back(slide);
}

void Document::addSlide(std::shared_ptr<Slide> slide, size_t number) {
    auto it = slides.begin();
    std::advance(it, number);
    slides.insert(it, slide);
}

void Document::removeSlide(size_t number) {
    auto it = slides.begin();
    std::advance(it, number);
    slides.erase(it); 
}

void Document::removeSlide(std::shared_ptr<Slide> slide) {
    slides.erase(std::remove(slides.begin(), slides.end(), slide), slides.end());
}

std::shared_ptr<Slide> Document::getSlide(size_t number) const {
    
    return (!slides.empty()) ? slides.at(number) : nullptr;
}

size_t Document::size() const {
    return slides.size();
}

Document::Document() {
    slides.push_back(std::make_shared<Slide>());
}

DocumentContainer::iterator Document::begin() {
    return slides.begin();
}

DocumentContainer::const_iterator Document::cbegin() const {
    return slides.cbegin();
}

DocumentContainer::iterator Document::end() {
    return slides.end();
}

DocumentContainer::const_iterator Document::cend() const {
    return slides.cend();
}

DocumentContainer::reverse_iterator Document::rbegin() {
    return slides.rbegin();
}

DocumentContainer::const_reverse_iterator Document::crbegin() const {
    return slides.crbegin();
}

DocumentContainer::reverse_iterator Document::rend() {
    return slides.rend();
}

DocumentContainer::const_reverse_iterator Document::crend() const {
    return slides.crend();
}





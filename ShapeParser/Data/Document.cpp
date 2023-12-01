#include "Document.hpp"

std::vector<std::shared_ptr<Slide>> Document::getAllSlides() const {
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
    std::cout << "Getting slide " << number << std::endl;
    std::cout << "Slides size: " << slides.size() << std::endl; // this line prints "Slides size: 1
    std::shared_ptr<Slide> slide = (!slides.empty()) ? slides.at(number) : nullptr; // this line is the problem
    std::cout << "Slide " << number << " returned" << std::endl;
    return slide;
}

size_t Document::size() const {
    return slides.size();
}

Document::Document() {
    std::cout << "Document created" << std::endl;
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





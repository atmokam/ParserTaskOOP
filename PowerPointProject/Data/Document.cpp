#include <algorithm>
#include "Document.hpp"
#include "Slide.hpp"
#include "Serialization/Converter.hpp"



void Document::addSlide(std::shared_ptr<Slide> slide, size_t number) 
{
    if(number == -1){
        slides.push_back(slide);
        return;
    }
    auto it = slides.begin();
    std::advance(it, number);
    slides.insert(it, slide);
}

void Document::removeSlide(size_t number) 
{
    auto it = slides.begin();
    std::advance(it, number);
    slides.erase(it); 
}

size_t Document::generateID() 
{
    return maxID++;
}

size_t Document::getMaximumID() const 
{
    return maxID;
}

void Document::setMaximumID(size_t id) 
{
    maxID = id;
}


std::shared_ptr<Slide> Document::getSlide(size_t number) const 
{
    return (!slides.empty()) ? slides.at(number) : nullptr;
}

size_t Document::size() const 
{
    return slides.size();
}

Document::Document() 
{
    Converter converter;
    slides.push_back(std::make_shared<Slide>());
    defaultAttributes.setLineWidth(1);
    defaultAttributes.setHexFillColor(converter.convertToColor("#FFFFFF"));
    defaultAttributes.setHexLineColor(converter.convertToColor("#000000"));
    defaultAttributes.setLineType(converter.convertToLineType("solid"));

}

Attributes Document::getDefaultAttributes() const 
{
    return defaultAttributes;
}

std::vector<std::shared_ptr<Slide>>::iterator Document::begin() 
{
    return slides.begin();
}

std::vector<std::shared_ptr<Slide>>::const_iterator Document::cbegin() const 
{
    return slides.cbegin();
}

std::vector<std::shared_ptr<Slide>>::iterator Document::end() 
{
    return slides.end();
}

std::vector<std::shared_ptr<Slide>>::const_iterator Document::cend() const 
{
    return slides.cend();
}

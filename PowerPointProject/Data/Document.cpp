#include <algorithm>
#include "Document.hpp"
#include "Slide.hpp"
#include "Serialization/Converter.hpp"
#include "Renderer/Formatting/FormatLibrary.hpp"

namespace Data 
{

    Document::Document() 
    {
        Renderer::Formatting::FormatLibrary formatMap;
        Serialization::Converter converter;
        slides.push_back(std::make_shared<Slide>());

        defaultAttributes = std::make_shared<Attributes>();
        defaultAttributes->setLineWidth(1);
        defaultAttributes->setHexFillColor(converter.convertToColor("#FFFFFF"));
        defaultAttributes->setHexLineColor(converter.convertToColor("#000000"));
        defaultAttributes->setLineType(converter.convertToLineType("solid"));
        defaultAttributes->setHexTextColor(converter.convertToColor("#000000"));
        defaultAttributes->setFontSize(12);
        defaultAttributes->setText("");
        defaultAttributes->setHexTextColor(converter.convertToColor("#000000"));
        
        format = formatMap.getFormat("A4");

        generator = std::make_shared<IDGenerator>();

    }

    std::pair<double, double> Document::getFormat() const 
    {
        return format;
    }

    void Document::setFormat(const std::pair<double, double>& format) 
    {
        this->format = format;
    }

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


    std::shared_ptr<IDGenerator> Document::getIDGenerator() 
    {
        return generator;
    }


    std::shared_ptr<Slide> Document::getSlide(size_t number) const 
    {
        return (!slides.empty()) ? slides.at(number) : nullptr;
    }

    size_t Document::size() const 
    {
        return slides.size();
    }


    std::shared_ptr<Attributes> Document::getDefaultAttributes() const 
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
}
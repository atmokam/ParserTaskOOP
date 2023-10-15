#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <iostream>
#include <string>

#include "Slide.hpp"

class Document
{
    std::vector<std::shared_ptr<Slide>> slides;
public:

    Document();
    std::vector<std::shared_ptr<Slide>> getAllSlides() const;
    void addSlide(std::shared_ptr<Slide> slide);


    std::shared_ptr<Slide> getSlide(size_t current) const;
};

#endif

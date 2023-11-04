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
    void removeSlide(size_t number);

    std::vector<std::shared_ptr<Slide>>::iterator begin() ;
    std::vector<std::shared_ptr<Slide>>::const_iterator cbegin() const;
    std::vector<std::shared_ptr<Slide>>::iterator end() ;
    std::vector<std::shared_ptr<Slide>>::const_iterator cend() const;

    std::vector<std::shared_ptr<Slide>>::reverse_iterator rbegin() ;
    std::vector<std::shared_ptr<Slide>>::const_reverse_iterator crbegin() const;
    std::vector<std::shared_ptr<Slide>>::reverse_iterator rend() ;
    std::vector<std::shared_ptr<Slide>>::const_reverse_iterator crend() const;


    std::shared_ptr<Slide> getSlide(size_t number) const;
};

#endif

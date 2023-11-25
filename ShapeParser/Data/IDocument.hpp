#ifndef IDOCUMENT_HPP
#define IDOCUMENT_HPP

#include <iostream>
#include <string>

#include "Slide.hpp"

using DocumentContainer = std::vector<std::shared_ptr<Slide>>;

class IDocument {
public:

    virtual DocumentContainer getAllSlides() const = 0;
    virtual void addSlide(std::shared_ptr<Slide> slide) = 0;
    virtual void addSlide(std::shared_ptr<Slide> slide, size_t number) = 0;
    virtual void removeSlide(std::shared_ptr<Slide> slide) = 0;
    virtual void removeSlide(size_t number) = 0;
    virtual size_t size() const = 0;

    virtual DocumentContainer::iterator begin()  = 0;
    virtual DocumentContainer::const_iterator cbegin() const = 0;
    virtual DocumentContainer::iterator end()  = 0;
    virtual DocumentContainer::const_iterator cend() const = 0;

    virtual DocumentContainer::reverse_iterator rbegin()  = 0;
    virtual DocumentContainer::const_reverse_iterator crbegin() const = 0;
    virtual DocumentContainer::reverse_iterator rend()  = 0;
    virtual DocumentContainer::const_reverse_iterator crend() const = 0;


    virtual std::shared_ptr<Slide> getSlide(size_t number) const = 0;
};

#endif

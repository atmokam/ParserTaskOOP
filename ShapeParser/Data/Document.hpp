#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <iostream>
#include <string>

#include "Slide.hpp"
#include "IDocument.hpp"

using DocumentContainer = std::vector<std::shared_ptr<Slide>>;

class Document : public IDocument {
    DocumentContainer slides;
public:

    Document();
    DocumentContainer getAllSlides() const override;
    void addSlide(std::shared_ptr<Slide> slide) override;
    void addSlide(std::shared_ptr<Slide> slide, size_t number) override;
    void removeSlide(std::shared_ptr<Slide> slide) override;
    void removeSlide(size_t number) override;
    size_t size() const override;

    DocumentContainer::iterator begin()  override;
    DocumentContainer::const_iterator cbegin() const override;
    DocumentContainer::iterator end()  override;
    DocumentContainer::const_iterator cend() const override;

    DocumentContainer::reverse_iterator rbegin()  override;
    DocumentContainer::const_reverse_iterator crbegin() const override;
    DocumentContainer::reverse_iterator rend()  override;
    DocumentContainer::const_reverse_iterator crend() const override;


    std::shared_ptr<Slide> getSlide(size_t number) const override;
};

#endif

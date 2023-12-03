#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <iostream>
#include <string>
#include <memory>

#include "IDocument.hpp"


class Document : public IDocument {
    DocumentContainer slides;
public:

    Document();
 
    // [TK] Bad API, document container is the Document itself
    DocumentContainer getAllSlides() const override;

    void addSlide(std::shared_ptr<Slide> slide) override;
    // [TK] no need to duplicate API, slide position could have default value -1 which will mean append to the end
    void addSlide(std::shared_ptr<Slide> slide, size_t number) override;
    // 
    void removeSlide(std::shared_ptr<Slide> slide) override;
    // [TK] keep only this version of removeSlide
    void removeSlide(size_t number) override;
    size_t size() const override;

    DocumentContainer::iterator begin()  override;
    DocumentContainer::const_iterator cbegin() const override;
    DocumentContainer::iterator end()  override;
    DocumentContainer::const_iterator cend() const override;

    // [TK] Do you really need reverse iterators?
    DocumentContainer::reverse_iterator rbegin()  override;
    DocumentContainer::const_reverse_iterator crbegin() const override;
    DocumentContainer::reverse_iterator rend()  override;
    DocumentContainer::const_reverse_iterator crend() const override;

    // [TK] what is number, Slide ID or index?
    std::shared_ptr<Slide> getSlide(size_t number) const override;
};

#endif

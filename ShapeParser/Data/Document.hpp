#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <string>
#include <memory>
#include <vector>

#include "Include/IDocument.hpp"

class Slide;


class Document : public IDocument {
    std::vector<std::shared_ptr<Slide>> slides;
public:
    Document();
 
    // [TK] Bad API, document container is the Document itself

    // [TK] no need to duplicate API, slide position could have default value -1 which will mean append to the end
    void addSlide(std::shared_ptr<Slide> slide, size_t index = -1);
    // [TK] keep only this version of removeSlide
    void removeSlide(size_t index);
    size_t size() const;

    std::vector<std::shared_ptr<Slide>>::iterator begin() ;
    std::vector<std::shared_ptr<Slide>>::const_iterator cbegin() const;
    std::vector<std::shared_ptr<Slide>>::iterator end() ;
    std::vector<std::shared_ptr<Slide>>::const_iterator cend() const;

    // [TK] Do you really need reverse iterators?

    // [TK] what is number, Slide ID or index?
    std::shared_ptr<Slide> getSlide(size_t index) const;
};

#endif

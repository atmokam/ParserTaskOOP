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
 

    void addSlide(std::shared_ptr<Slide> slide, size_t index = -1);
    void removeSlide(size_t index);
    size_t size() const;

    std::vector<std::shared_ptr<Slide>>::iterator begin() ;
    std::vector<std::shared_ptr<Slide>>::const_iterator cbegin() const;
    std::vector<std::shared_ptr<Slide>>::iterator end() ;
    std::vector<std::shared_ptr<Slide>>::const_iterator cend() const;


    // [TK] what is number, Slide ID or index?
    std::shared_ptr<Slide> getSlide(size_t index) const;
};

#endif

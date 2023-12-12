#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <string>
#include <memory>
#include <vector>

#include "Include/IDocument.hpp"
#include "ItemAttributes.hpp"
#include "Format.hpp"

class Slide;



class Document : public IDocument {
    std::vector<std::shared_ptr<Slide>> slides;
    std::pair<double, double> format;
    Attributes defaultAttributes;
    
    size_t maxID = 0;
public:
    Document();
 

    void addSlide(std::shared_ptr<Slide> slide, size_t index = -1) override;
    void removeSlide(size_t index) override;
    size_t size() const override;
    size_t getMaximumID() const override;
    void setMaximumID(size_t id) override;
    size_t generateID() override;
    Attributes getDefaultAttributes() const override;

    std::vector<std::shared_ptr<Slide>>::iterator begin()  override;
    std::vector<std::shared_ptr<Slide>>::const_iterator cbegin() const override;
    std::vector<std::shared_ptr<Slide>>::iterator end()  override;
    std::vector<std::shared_ptr<Slide>>::const_iterator cend() const override;


    std::shared_ptr<Slide> getSlide(size_t index) const override;
};

#endif

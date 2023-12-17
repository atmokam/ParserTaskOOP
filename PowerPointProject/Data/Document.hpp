#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <string>
#include <memory>
#include <vector>

#include "Include/IDocument.hpp"
#include "ItemAttributes.hpp"
#include "IDGenerator.hpp"


namespace Data 
{    
    class Slide;
    
    class Document : public IDocument {
        std::vector<std::shared_ptr<Slide>> slides;
        std::pair<double, double> format;
        Attributes defaultAttributes;
        
        IDGenerator generator;
    public:
        Document();
    
        
        void addSlide(std::shared_ptr<Slide> slide, size_t index = -1) override;
        void removeSlide(size_t index) override;
        size_t size() const override;

        IDGenerator& getIDGenerator() override;

        Attributes getDefaultAttributes() const override;
        std::pair<double, double> getFormat() const override;
        void setFormat(const std::pair<double, double>& format) override;

        std::vector<std::shared_ptr<Slide>>::iterator begin()  override;
        std::vector<std::shared_ptr<Slide>>::const_iterator cbegin() const override;
        std::vector<std::shared_ptr<Slide>>::iterator end()  override;
        std::vector<std::shared_ptr<Slide>>::const_iterator cend() const override;


        std::shared_ptr<Slide> getSlide(size_t index) const override;
    };
}
#endif

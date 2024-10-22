#ifndef IDOCUMENT_HPP
#define IDOCUMENT_HPP


#include <string>
#include <memory>
#include <vector>


namespace Data
{
    class Slide;
    class Attributes;
    class IDGenerator;
    
    class IDocument {
    public:

        virtual void addSlide(std::shared_ptr<Slide> slide, size_t number = -1) = 0;
        virtual void removeSlide(size_t number) = 0;
        virtual size_t size() const = 0;

        virtual std::shared_ptr<IDGenerator> getIDGenerator() = 0;

        virtual std::shared_ptr<Attributes> getDefaultAttributes() const = 0;
        virtual ~IDocument() = default;
        virtual std::pair<double, double> getFormat() const = 0;
        virtual void setFormat(const std::pair<double, double>& format) = 0;

        virtual std::vector<std::shared_ptr<Slide>>::iterator begin()  = 0;
        virtual std::vector<std::shared_ptr<Slide>>::const_iterator cbegin() const = 0;
        virtual std::vector<std::shared_ptr<Slide>>::iterator end()  = 0;
        virtual std::vector<std::shared_ptr<Slide>>::const_iterator cend() const = 0;


        virtual std::shared_ptr<Slide> getSlide(size_t number) const = 0;
    };
}

#endif

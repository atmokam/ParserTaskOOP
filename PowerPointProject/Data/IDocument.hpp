#ifndef IDOCUMENT_HPP
#define IDOCUMENT_HPP


#include <string>
#include <memory>
#include <vector>

class Slide;
class Attributes;

class IDocument {
public:

    virtual void addSlide(std::shared_ptr<Slide> slide, size_t number) = 0;
    virtual void removeSlide(size_t number) = 0;
    virtual size_t size() const = 0;
    virtual size_t generateID() = 0;
    virtual size_t getMaximumID() const = 0;
    virtual void setMaximumID(size_t id) = 0;
    virtual Attributes getDefaultAttributes() const = 0;
    virtual ~IDocument() = default;

    virtual std::vector<std::shared_ptr<Slide>>::iterator begin()  = 0;
    virtual std::vector<std::shared_ptr<Slide>>::const_iterator cbegin() const = 0;
    virtual std::vector<std::shared_ptr<Slide>>::iterator end()  = 0;
    virtual std::vector<std::shared_ptr<Slide>>::const_iterator cend() const = 0;


    virtual std::shared_ptr<Slide> getSlide(size_t number) const = 0;
};

#endif

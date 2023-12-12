#ifndef ISHAPE_HPP
#define ISHAPE_HPP

#include <memory>

class IShape {
public:
    virtual std::shared_ptr<IShape> clone() const = 0;
};


#endif
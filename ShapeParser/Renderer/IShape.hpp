#ifndef ISHAPE_HPP
#define ISHAPE_HPP

#include <string>
#include <ostream>


#include "ITextDisplayable.hpp"


class IShape {
public:
    virtual std::unique_ptr<IShape> clone() const = 0;
    virtual ~IShape() = default;
};


#endif
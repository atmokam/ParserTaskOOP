#ifndef ISHAPE_HPP
#define ISHAPE_HPP

#include <string>
#include <ostream>


#include "ITextDisplayable.hpp"


class IShape : public ITextDisplayable {
public:
    virtual void print(std::ostream& stream) = 0;
};


#endif
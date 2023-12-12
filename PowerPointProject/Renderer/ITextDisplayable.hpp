#ifndef ITEXTDISPLAYABLE_HPP
#define ITEXTDISPLAYABLE_HPP

#include <ostream>

class ITextDisplayable {
public:
    virtual void print(std::ostream& stream) = 0;
};

#endif
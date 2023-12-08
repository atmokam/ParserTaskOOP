#ifndef ITEXTDISPLAYABLE_HPP
#define ITEXTDISPLAYABLE_HPP

#include <string>
#include <ostream>

class ITextDisplayable {
public:
    virtual void print(std::ostream& stream) = 0;
};

#endif
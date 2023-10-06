#ifndef OUTPUTPRINTER_HPP
#define OUTPUTPRINTER_HPP

#include <iostream>
#include <string>

#include "ItemAttributes.hpp"

class OutputPrinter {
    std::ostream& stream;

    Type type;
    Position position;
    BoundingRect boundingRect;
    Color color;

public:
    OutputPrinter(Type type, std::ostream& stream = std::cout);
    OutputPrinter(Position position, std::ostream& stream = std::cout);
    OutputPrinter(BoundingRect boundingRect, std::ostream& stream = std::cout);
    OutputPrinter(Color color, std::ostream& stream = std::cout);

    std::ostream& operator<<(Type type);
    std::ostream& operator<<(Position position);
    std::ostream& operator<<(BoundingRect boundingRect);
    std::ostream& operator<<(Color color);

};

#endif
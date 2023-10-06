#include "OutputPrinter.hpp"

OutputPrinter::OutputPrinter(Type type, std::ostream& stream) : type(type), stream(stream) {}

OutputPrinter::OutputPrinter(Position position, std::ostream& stream) : position(position), stream(stream) {}

OutputPrinter::OutputPrinter(BoundingRect boundingRect, std::ostream& stream) : boundingRect(boundingRect), stream(stream) {}

OutputPrinter::OutputPrinter(Color color, std::ostream& stream) : color(color), stream(stream) {}

std::ostream& OutputPrinter::operator<<(Type type) {
    switch (type) {
        case Type::Rectangle:
            return stream << "Rectangle";
        case Type::Trapezoid:
            return stream << "Trapezoid";
        case Type::Ellipse:
            return stream << "Ellipse";
        case Type::Line:
            return stream << "Line";
        case Type::Triangle:
            return stream << "Triangle";
        default:
            return stream;
    }
}

std::ostream& OutputPrinter::operator<<(Position position) {
    std::vector<double> coordinates = position.getCoordinates();
    stream << " at indices ( ";
    for (int i = 0; i < coordinates.size(); i++) {
        stream << coordinates[i];
        if (i != coordinates.size() - 1) {
            stream << ", ";
        }
    }
    stream << " )";
    return stream;
}

// how can this be used in code?
// example: 

std::ostream& OutputPrinter::operator<<(BoundingRect boundingRect) {
    stream << "Width: " << boundingRect.width << ", Height: " << boundingRect.height;
    return stream;
}

std::ostream& OutputPrinter::operator<<(Color color) {
    stream << "Line color: #" << std::hex << color.hexLineColor << ", Fill color: #" << std::hex << color.hexFillColor;
    return stream;
}



#include "Renderer.hpp"

void Renderer::renderText(std::ostream& os, const std::shared_ptr<Slide>& slide) {
    for(auto& item : *slide) {
        renderText(os, item.second);
    }
}

void Renderer::renderText(std::ostream& os, const std::shared_ptr<Document>& document) {
    for(auto& slide : *document) {
        renderText(os, slide);
    }
}

void Renderer::renderImage(std::shared_ptr<Slide>& slide) {
    std::cout << "Rendering slide image" << std::endl;
}

void Renderer::renderText(std::ostream &os, const std::shared_ptr<Item>& item) {
    os << item->getID() << std::endl;
    os << ShapeType{item->getType()} << std::endl;
    os << item->getPosition() << std::endl;
    os << item->getBoundingRect() << std::endl;
    os << item->getColor() << std::endl;
    os << item->getLineDescriptor() << std::endl;
}

void Renderer::renderImage(std::shared_ptr<Item>& item) {
    std::cout << "Rendering item image" << std::endl;
}

inline std::ostream& operator<<(std::ostream& os, const LineDescriptor& line) {
    os << "Line_style: ";
    switch (line.type) {
        case LineType::Solid:
            os << "solid" << std::endl;
            break;
        case LineType::Dashed:
            os << "dashed" << std::endl;
            break;
        case LineType::Dotted:
            os << "dotted" << std::endl;
            break;
    }
    os << "Line_width: " << line.width;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const ShapeType& shape) {
        os << "Type: ";
    switch (shape.type) {
        case Type::Rectangle:
            return os << "Rectangle";
        case Type::Trapezoid:
            return os << "Trapezoid";
        case Type::Ellipse:
            return os << "Ellipse";
        case Type::Line:
            return os << "Line";
        case Type::Triangle:
            return os << "Triangle";
        default:
            return os;
    }
}



inline std::ostream& operator<<(std::ostream& os, const Position& position) {
    std::vector<double> coordinates = position.getCoordinates();
    os << "Indices: ";
    for (int i = 0; i < coordinates.size(); i++) {
        os << coordinates[i];
        if (i != coordinates.size() - 1) {
            os << ", ";
        }
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const BoundingRect& boundingRect) {
    os << "Width: " << boundingRect.width << std::endl;
    os << "Height: " << boundingRect.height;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Color& color) {
    os << "Line_color: #" << std::hex << color.hexLineColor << std::endl;
    os << "Fill_color: #" << std::hex << color.hexFillColor;
    return os;
}


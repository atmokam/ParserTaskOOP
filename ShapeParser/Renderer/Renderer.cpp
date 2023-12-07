#include "Renderer.hpp"
#include "Data/Item.hpp"
#include "Data/Slide.hpp"
#include "Data/Document.hpp"


// void Renderer::renderText(std::ostream& os, const std::shared_ptr<Slide>& slide, const size_t slideNumber) {
//     os << "Slide: " << slideNumber << std::endl;
//     for(const auto& item : *slide) {
//         renderText(os, item.second);
//     }
// }

void Renderer::renderText(std::ostream& os, const std::shared_ptr<Document>& document) {
    size_t slideNumber = 0;
    for(const auto& slide : *document) {
        renderText(os, slide, slideNumber++);
    }
}

void Renderer::renderImage(std::shared_ptr<Slide>& slide) {
    std::cout << "Rendering slide image" << std::endl;
}

void Renderer::renderText(std::ostream &os, const std::shared_ptr<Item>& item) {
    // os << item->getID() << std::endl;
    // shapeToText(os, ShapeType{item->getType()}) ;
    // positionToText(os, item->getPosition());
    // boundingRectToText(os, item->getBoundingRect());
    // colorToText(os, item->getColor());
    // lineDescriptorToText(os, item->getLineDescriptor());
}

void Renderer::renderImage(std::shared_ptr<Item>& item) {
    std::cout << "Rendering item image" << std::endl;
}

void Renderer::lineDescriptorToText(std::ostream& os, const LineDescriptor line) {
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
    os << std::endl;

}

void Renderer::shapeToText(std::ostream& os, const ShapeType& shape) {
        os << "Type: ";
    switch (shape.getType()) {
        case Type::Rectangle:
             os << "Rectangle";
            break;
        case Type::Trapezoid:
             os << "Trapezoid";
             break;
        case Type::Ellipse:
             os << "Ellipse";
             break;
        case Type::Line:
             os << "Line";
             break;
        case Type::Triangle:
             os << "Triangle";
             break;
        default:
            os << std::endl;
            
    }
    os << std::endl;
}



void Renderer::positionToText(std::ostream& os, const Position& position) {
    std::vector<double> coordinates = position.getCoordinates();
    os << "Indices: ";
    for (int i = 0; i < coordinates.size(); i++) {
        os << coordinates[i];
        if (i != coordinates.size() - 1) {
            os << ", ";
        }
    }
    os << std::endl;
}

// void Renderer::boundingRectToText(std::ostream& os, const Dimentions& boundingRect) {
//     os << "Width: " << boundingRect.width << std::endl;
//     os << "Height: " << boundingRect.height;
//     os << std::endl;
// }

void Renderer::colorToText(std::ostream& os, const Color& color) {
    os << "Line_color: #" << std::hex << color.hexLineColor << std::endl;
    os << "Fill_color: #" << std::hex << color.hexFillColor;
    os << std::endl;
}


#ifndef VIEW_HPP
#define VIEW_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

#include "Document.hpp"
#include "Item.hpp"
#include "Slide.hpp"

class View {
public:
    View() = default;

    size_t currentSlideNumber = 0;

    void displayItem(std::shared_ptr<Item> item);
    void displaySlide(std::shared_ptr<Slide> slide);
    void displayDocument(std::shared_ptr<Document> document);

    void changeSlide(size_t slideNumber);
};


#endif


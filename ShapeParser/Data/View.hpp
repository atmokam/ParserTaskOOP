#ifndef VIEW_HPP
#define VIEW_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

#include "Data/Document.hpp"
#include "Data/Item.hpp"
#include "Data/Slide.hpp"

class View {
public:
    View(std::shared_ptr<Document> document);
    View() = default;

    size_t currentSlideNumber = 0;
    std::shared_ptr<Slide> currentSlide;

    void displayItem(std::shared_ptr<Item> item);
    void displaySlide(std::shared_ptr<Slide> slide);
    void displayDocument(std::shared_ptr<Document> document);

    
};


#endif


#include "View.hpp"

void View::displayItem(std::shared_ptr<Item> item) {
    
}

void View::displaySlide(std::shared_ptr<Slide> slide) {
    
}

void View::displayDocument(std::shared_ptr<Document> document) {
    // some qt code, i have no idea for now
}


View::View(std::shared_ptr<Document> document){ // when view is created, it is set to the first slide
    currentSlide = *document->begin();
}


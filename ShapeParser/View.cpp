#include "View.hpp"

void View::displayItem(std::shared_ptr<Item> item) {
    //std::cout << item->toString() << std::endl;
}

void View::displaySlide(std::shared_ptr<Slide> slide) {
    //std::cout << slide->toString() << std::endl;
}

void View::displayDocument(std::shared_ptr<Document> document) {
    //std::cout << document->toString() << std::endl;
}

void View::changeSlide(size_t slideNumber) {
    currentSlideNumber = slideNumber;
}

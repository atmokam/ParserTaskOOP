#include "SaveLoadSerializer.hpp"


void SaveLoadSerializer::save(std::shared_ptr<Document> document, const std::string& path) {
    std::ofstream file;

    
    file.open(path + ".ppx");

    if(!file.is_open()){
        throw std::invalid_argument("Invalid path or filename");
    }

    size_t size = std::distance(document->cbegin(), document->cend());

    for(size_t i = 0; i < size; ++i){
        file << "slide:" << i << std::endl;
        file << "max_id:"  << document->getSlide(i)->getMaximumID() << std::endl;
        saveToFile(file, document->getSlide(i)->getItems());
    }

}

void SaveLoadSerializer::saveToFile(std::ofstream& file, const std::unordered_map<int, std::shared_ptr<Item>>& items) {
    for(auto item : items) {
        file << "id:" << item.second->getID() << std::endl;
        file << ShapeType{item.second->getType()} << std::endl;
        file << item.second->getPosition() << std::endl;
        file << item.second->getBoundingRect() << std::endl;
        file << item.second->getColor() << std::endl;
        file << std::endl;
    }
}

std::shared_ptr<Document> SaveLoadSerializer::load(const std::string& path) { 
    // load document and update view
    std::cout << "LoadCommand executed" << std::endl;

    std::ifstream file;

    file.open(path);
    if(!file.is_open()){
        throw std::invalid_argument("Invalid path or filename");
    }

    std::string line; // separate this create item function
    Position pos; Type type; BoundingRect boundingRect; Color color; //int id; int max_id;
    while (std::getline(file, line))
    {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, ':'))
        {
            std::string value;
            if (std::getline(is_line, value))
            {
                std::cout<< key << " " << value << std::endl;
                // initialize all members, then construct a make_shared item
            }
        }
    }


} 


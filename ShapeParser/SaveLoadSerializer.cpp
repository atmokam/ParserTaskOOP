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
        file << item.second->getLineDescriptor() << std::endl;
        file << std::endl;
    }
}

std::shared_ptr<Document> SaveLoadSerializer::load(const std::string& path) { 
    std::ifstream file;

    file.open(path);
    if(!file.is_open()){
        throw std::invalid_argument("Invalid path or filename");
    }

    return readFromFile(file);
    
} 


std::shared_ptr<Document> SaveLoadSerializer::readFromFile(std::ifstream& file) {
    std::shared_ptr<Document> document = std::make_shared<Document>();

    std::string line; 
    Position pos; Type type; BoundingRect boundingRect; Color color; ID id; LineDescriptor lineDescriptor;
    while (std::getline(file, line))
    {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, ':'))
        {
            std::string value;
            if (std::getline(is_line, value))
            {
                if(key == "id")               
                    id = Converter::convertToID(value);
                else if(key == "type")
                    type = Converter::convertToType(value);
                else if(key == "indices")
                    pos = Converter::convertToPosition(value, ' '); 
                else if(key == "width")
                    boundingRect.width = std::stod(value);
                else if(key == "height")
                    boundingRect.height = std::stod(value);
                else if(key == "line_color")
                    color.hexLineColor = Converter::convertToColor(value);
                else if(key == "fill_color")
                    color.hexFillColor = Converter::convertToColor(value);
                else if(key == "line_width")
                    lineDescriptor.width = std::stod(value);
                else if(key == "line_style"){
                    lineDescriptor.type = Converter::convertToLineType(value);
                    (*std::prev(document->end()))->addItem(std::make_shared<Item>(type, pos, boundingRect, color, id, lineDescriptor));
                }
                else if(key == "max_id")
                    (*(std::prev(document->end())))->setMaximumID(std::stoi(value));
                else if(key == "slide"){
                    if(value == "0")
                        continue;
                    document->addSlide(std::make_shared<Slide>());
                }
                else {
                    throw std::invalid_argument("Invalid file contents");
                }

            }
        }

    }

    return document;
}

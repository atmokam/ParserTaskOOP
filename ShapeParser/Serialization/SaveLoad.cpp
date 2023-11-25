#include "SaveLoad.hpp"


void SaveLoadSerializer::save(std::shared_ptr<Document> document, const std::string& path) {
    std::ofstream file;
    
    file.open(path + ".ppx");

    if(!file.is_open()){
        throw std::invalid_argument("Invalid path or filename");
    }

    size_t size = std::distance(document->cbegin(), document->cend());

    for(size_t i = 0; i < size; ++i){
        file << "max_id:"  << document->getSlide(i)->getMaximumID() << std::endl;
        serialize(file, document->getSlide(i));
    }

}

void SaveLoadSerializer::serialize(std::ofstream& file, const std::shared_ptr<Slide>& slide) {
    for(auto item : *slide) {
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

    return std::make_shared<Document>(deserialize(file));
    
} 


Document SaveLoadSerializer::deserialize(std::ifstream& file) {
    Document document = Document();

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
                else if(key == "line_style")
                    lineDescriptor.type = Converter::convertToLineType(value);
                else if(key == "line_width"){
                    lineDescriptor.width = std::stod(value);
                    (*std::prev(document.end()))->addItem(std::make_shared<Item>(type, pos, boundingRect, color, id, lineDescriptor));
                }
                else if(key == "max_id")
                    (*(std::prev(document.end())))->setMaximumID(std::stoi(value));
                else if(key == "slide"){
                    if(value == "0")
                        continue;
                    document.addSlide(std::make_shared<Slide>());
                }
                else {
                    std::cout << key << " " << value << std::endl;
                    throw std::invalid_argument("Invalid file contents");
                }

            }
        }

    }

    return document;
}


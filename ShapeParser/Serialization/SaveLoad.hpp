#ifndef SAVELOADSERIALIZER_HPP
#define SAVELOADSERIALIZER_HPP
// this class is responsible for saving the document to device and loading from device

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

#include "Data/Document.hpp"
#include "Converter.hpp"

class SaveLoadSerializer {
    static void serialize(std::ofstream& file, const std::unordered_map<int, std::shared_ptr<Item>>& items);
    static std::shared_ptr<Document> deserialize(std::ifstream& file);
public:
    static void save(std::shared_ptr<Document> document, const std::string& path);
    static std::shared_ptr<Document> load(const std::string& path);
};

#endif



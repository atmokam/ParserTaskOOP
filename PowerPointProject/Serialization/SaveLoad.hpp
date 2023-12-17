#ifndef SAVELOADSERIALIZER_HPP
#define SAVELOADSERIALIZER_HPP
// this class is responsible for saving the Document to device and loading from device

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>


#include "Data/ItemAttributes.hpp"

class IDocument;
class Slide;
class QJsonDocument;
class QJsonArray;
class QJsonObject;
class QJsonValueRef;
class ItemBase;
class ItemLeaf;

class SaveLoad {
    QJsonObject serializeLeaf(const std::shared_ptr<ItemLeaf>& item);
    std::shared_ptr<ItemLeaf> deserializeLeaf(const QJsonObject& object);
    void recursiveSerialize(const std::shared_ptr<ItemBase>& item, QJsonArray& slideArray);
    void recursiveDeserialize(QJsonValueRef& item, const std::shared_ptr<Slide>& slide);
public:
    void save(const std::shared_ptr<IDocument>& document, QJsonDocument& stream);
    void load(QJsonDocument& stream, const std::shared_ptr<IDocument>& document);
};





#endif



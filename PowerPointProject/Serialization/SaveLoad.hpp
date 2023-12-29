#ifndef SAVELOADSERIALIZER_HPP
#define SAVELOADSERIALIZER_HPP

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>


#include "Data/Item/ItemAttributes.hpp"
#include "Data/Item/ItemBase.hpp"
#include "Data/Slide.hpp"
#include "Include/IDocument.hpp"

class QJsonDocument;
class QJsonArray;
class QJsonObject;
class QJsonValueRef;

namespace Serialization
{
    class SaveLoad {
        QJsonObject serializeLeaf(const std::shared_ptr<Data::ItemLeaf>& item);
        std::shared_ptr<Data::ItemLeaf> deserializeLeaf(const QJsonObject& object);
        void recursiveSerialize(const std::shared_ptr<Data::ItemBase>& item, QJsonArray& slideArray);
        void recursiveDeserialize(QJsonValueRef& item, const std::shared_ptr<Data::Slide>& slide);
    public:
        void save(const std::shared_ptr<Data::IDocument>& document, QJsonDocument& stream);
        void load(QJsonDocument& stream, const std::shared_ptr<Data::IDocument>& document);
    };
}


#endif



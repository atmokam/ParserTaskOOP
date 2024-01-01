#ifndef SERIALIZERVISITOR_HPP
#define SERIALIZERVISITOR_HPP
// serialize to json

#include <memory>

#include "Data/Item/ItemAttributes.hpp"
#include "Data/Item/ItemBase.hpp"
#include "Data/Slide.hpp"
#include "Include/IDocument.hpp"
#include "Data/Item/IItemVisitor.hpp"
#include "JsonConverter.hpp"

#include <QJsonDocument>
#include <QJsonArray>

class QJsonObject;
class QJsonValueRef;

namespace Serialization
{
    class SerializerVisitor : public Data::IItemVisitor
    {
        std::shared_ptr<QJsonArray> currentSlideArray;
        std::reference_wrapper<QJsonDocument> output;

    public:
        SerializerVisitor(QJsonDocument& output);
        void visit(Data::ItemLeaf& item) override;
        void visit(Data::ItemGroup& item) override;
        void save(const std::shared_ptr<Data::IDocument>& document);
    };
}

#endif
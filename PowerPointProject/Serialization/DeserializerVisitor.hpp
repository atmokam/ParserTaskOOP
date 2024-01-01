#ifndef DESERIALIZERVISITOR_HPP
#define DESERIALIZERVISITOR_HPP

#include <string>
#include <memory>

#include "Include/IDocument.hpp"
#include "Data/Item/IItemVisitor.hpp"

class QJsonDocument;

namespace Serialization 
{
    class DeserializerVisitor: public Data::IItemVisitor
    {
        std::shared_ptr<Data::IDocument> docOutput;
        std::shared_ptr<QJsonValueRef> value;

        void deserializeHelper(QJsonValueRef& value);
    public:
        DeserializerVisitor(std::shared_ptr<Data::IDocument>& output);
        void visit(Data::ItemLeaf& item) override;
        void visit(Data::ItemGroup& item) override;
        void load(QJsonDocument& document);
    };

}


#endif
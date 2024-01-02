#ifndef DESERIALIZER_HPP
#define DESERIALIZER_HPP
//////////    This is the working version of deserializer.

#include <string>
#include <memory>
//////////    I attempted to use the visitor pattern in DeserializerVisitor.cpp
//////////    but I'm not sure about its implementation, so I left a note there.
//////////    If possible, would you please see it? Thank you very much.

class QJsonDocument;
class QJsonObject;
class QJsonArray;

namespace Data
{
    class IDocument;
}

namespace Serialization 
{
    class Deserializer
    {
        std::shared_ptr<Data::IDocument> docOutput;

        void deserialize(QJsonObject object);
        void deserialize(QJsonArray array);
    public:
        Deserializer(std::shared_ptr<Data::IDocument>& output);
        void load(QJsonDocument& document);
    };

}

#endif
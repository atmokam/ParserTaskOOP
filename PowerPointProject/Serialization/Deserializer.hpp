#ifndef DESERIALIZER_HPP
#define DESERIALIZER_HPP

#include <string>
#include <memory>


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
#include "JsonConverter.hpp"
#include <sstream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include "Renderer/Shape/ShapeLibrary.hpp"
#include "Application/Application.hpp"




// convert to json
namespace Serialization
{
    QJsonArray JsonConverter::convertToJson(const Data::Position& position) {
        QJsonArray result = QJsonArray();
        std::vector<double> values = position.getCoordinates();
        for (auto value : values) {
            result.append(value);
        }
        return result;
    }

    QJsonValue JsonConverter::convertToJson(const Renderer::Type& type) {
        switch (type) {
            case Renderer::Type::Line:
                return QJsonValue("line");
            case Renderer::Type::Rectangle:
                return QJsonValue("rectangle");
            case Renderer::Type::Trapezoid:
                return QJsonValue("trapezoid");
            case Renderer::Type::Ellipse:
                return QJsonValue("ellipse");
            case Renderer::Type::Triangle:
                return QJsonValue("triangle");
            case Renderer::Type::Group:
                return QJsonValue("group");
            default:
                return QJsonValue("");
        }
    }

    QJsonValue JsonConverter::convertToJson(const Data::LineType& lineType) 
    {
        switch (lineType) {
            case Data::LineType::Solid:
                return QJsonValue("solid");
            case Data::LineType::Dashed:
                return QJsonValue("dashed");
            case Data::LineType::Dotted:
                return QJsonValue("dotted");
            default:
                return QJsonValue("none");
        }
    }


    QJsonValue JsonConverter::convertToJson(const long& color) 
    {
        std::stringstream stream;
        stream << "#" << std::hex << color;
        return QJsonValue(QString::fromStdString(stream.str()));
    }


    QJsonValue JsonConverter::convertToJson(const Data::Attributes& attribute) 
    {
        App::Application& app = App::Application::getInstance();
        Data::Attributes defaultAttributes = app.getDocument()->getDefaultAttributes();
        QJsonObject result;

        result["lineWidth"] = attribute.getLineWidth().value(); 

        result["lineType"] = convertToJson(attribute.getLineType().value());

        result["lineColorHex"] = convertToJson(attribute.getHexLineColor().value());

        result["fillColorHex"] = convertToJson(attribute.getHexFillColor().value());

        result["text"] = QString::fromStdString(attribute.getText().value());

        return result;
    }


    QJsonValue JsonConverter::convertToJson(const Data::Geometry& geometry) 
    {
        QJsonObject result;

        result["position"] = convertToJson(geometry.getPosition().value());

        result["width"] = geometry.getWidth().value();

        result["height"] = geometry.getHeight().value();


        return result;
    }

    QJsonArray JsonConverter::convertToJson(const std::pair<double, double>& format)
    {
        QJsonArray result;
        result.append(format.first);
        result.append(format.second);
        return result;
    }

    QJsonValue JsonConverter::convertToJson(const std::vector<Data::ID>& ids)
    {
        QJsonArray result;
        for (auto id : ids) 
        {
            result.append(id);
        }
        return result;
    }



    // convert from json

    Data::Attributes JsonConverter::convertToAttributes(const QJsonValue& value) 
    {
        Data::Attributes result;
        QJsonObject object = value.toObject();
        result.setLineWidth(object["lineWidth"].toDouble());
        
        result.setLineType(convertToLineType(object["lineType"]));
       
        result.setHexLineColor(convertToColor(object["lineColorHex"]));

        result.setHexFillColor(convertToColor(object["fillColorHex"]));

        result.setText(object["text"].toString().toStdString());
        
        return result;
    }

    Data::Position JsonConverter::convertToPosition(const QJsonArray& array)
    {
        std::vector<double> result;
        for (auto value : array) {
            result.push_back(value.toDouble());
        }
        return Data::Position{result};
    }


    Data::Geometry JsonConverter::convertToGeometry(const QJsonValue& value) 
    {
        Data::Geometry result;
        QJsonObject object = value.toObject();
        
        result.setPosition(convertToPosition(object["position"].toArray()));
        
        result.setWidth(object["width"].toDouble());
       
        result.setHeight(object["height"].toDouble());
        
        return result;
    }


    std::pair<double, double> JsonConverter::convertToFormat(const QJsonArray& array)
    {
        return std::make_pair(array[0].toDouble(), array[1].toDouble());
    }


    Renderer::Type JsonConverter::convertToType(const QJsonValue& value) 
    {
        Renderer::ShapeLibrary shapeLibrary;
        return shapeLibrary.getType(value.toString().toStdString()).value(); 
    }

    Data::LineType JsonConverter::convertToLineType(const QJsonValue& value) 
    {
        if (value.toString() == "solid") 
        {
            return Data::LineType::Solid;
        } 
        else if (value.toString() == "dashed") 
        {
            return Data::LineType::Dashed;
        } 
        else if (value.toString() == "dotted") 
        {
            return Data::LineType::Dotted;
        } 
        else 
        {
            return Data::LineType::None;
        }
    }

    long JsonConverter::convertToColor(const QJsonValue& value)
    {
        std::string colorString = value.toString().toStdString();
        long converted = std::stol(colorString.substr(1), nullptr, 16);    
        return converted;
    }

    std::vector<Data::ID> JsonConverter::convertToIDs(const QJsonValue& value)
    {
        std::vector<Data::ID> result;
        QJsonArray array = value.toArray();
        for (auto id : array) 
        {
            result.push_back(id.toInt());
        }
        return result;
    }
}
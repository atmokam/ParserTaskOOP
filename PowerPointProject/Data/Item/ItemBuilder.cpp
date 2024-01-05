#include "ItemBuilder.hpp"
#include "Serialization/Converter.hpp"
#include "Renderer/Shape/ShapeLibrary.hpp"
#include "Include/IDocument.hpp"
#include "Application/Application.hpp"
#include "Data/IDGenerator.hpp"

namespace Data
{
    ItemBuilder::ItemBuilder(std::shared_ptr<ItemBase> item) : item(item) {}

    void ItemBuilder::buildItemLeaf(std::unordered_map<std::string, std::vector<std::string>>& operands)
    {
        App::Application& application = App::Application::getInstance();
        std::shared_ptr<IDocument> document = application.getDirector()->getDocument();
        Attributes defaultAttributes;
        Renderer::Type type;
        Serialization::Converter converter;

        item = std::make_shared<ItemLeaf>();
        defaultAttributes  = *document->getDefaultAttributes();
        type = Renderer::Type{converter.convertToType(operands["-name"][0])};
        item->setType(type);
        item->setID(document->getIDGenerator()->generateID());
            
        Geometry newGeometry;
        Attributes newAttributes; 

        trySetGeometry(operands, newGeometry);
        trySetAttributes(operands, newAttributes); 

        setDefaultGeometry(operands, newGeometry);
        setDefaultAttributes(operands, newAttributes);

        item->setAttributes(newAttributes);
        item->setGeometry(newGeometry);
        
    }

    void ItemBuilder::setDefaultGeometry(std::unordered_map<std::string, std::vector<std::string>> operands, Data::Geometry& geometry)
    {
        App::Application& application = App::Application::getInstance();
        std::shared_ptr<IDocument> document = application.getDirector()->getDocument();
        
        Serialization::Converter converter;
        // item always has a position
        
        if(operands.at("-name")[0] == "line")
        {
            while(operands["-pos"].size() < 4)
            {
                operands["-pos"].push_back("0");
            }
            geometry.setPosition(converter.convertToPosition(operands["-pos"]));
        }
        else
        {
            while(operands["-pos"].size() < 2)
            {
                operands["-pos"].push_back("0");
            }
            geometry.setPosition(converter.convertToPosition(operands["-pos"]));
        }
       

        if(!geometry.getWidth().has_value())
            geometry.setWidth(0);

        if(!geometry.getHeight().has_value())
            geometry.setHeight(0);
    }

    void ItemBuilder::setDefaultAttributes(std::unordered_map<std::string, std::vector<std::string>> operands, Data::Attributes& attributes)
    {
        App::Application& application = App::Application::getInstance();
        std::shared_ptr<IDocument> document = application.getDirector()->getDocument();
        Attributes defaultAttributes = *document->getDefaultAttributes();
        Serialization::Converter converter;

        if(!attributes.getHexLineColor().has_value())
            attributes.setHexLineColor(defaultAttributes.getHexLineColor().value());

        if(!attributes.getHexFillColor().has_value())
            attributes.setHexFillColor(defaultAttributes.getHexFillColor().value());
        
        if(!attributes.getLineWidth().has_value())
            attributes.setLineWidth(defaultAttributes.getLineWidth().value());
        
        if(!attributes.getLineType().has_value())
            attributes.setLineType(defaultAttributes.getLineType().value());

        if(!attributes.getText().has_value())
            attributes.setText(defaultAttributes.getText().value());

        if(!attributes.getHexTextColor().has_value())
            attributes.setHexTextColor(defaultAttributes.getHexTextColor().value());

        if(!attributes.getFontSize().has_value())
            attributes.setFontSize(defaultAttributes.getFontSize().value());
    }

    
    bool ItemBuilder::trySetGeometry(std::unordered_map<std::string, std::vector<std::string>> operands, Data::Geometry& geometry)
    {
        bool success = false;

        Serialization::Converter converter;
        if(operands.find("-pos") != operands.end()) 
        { 
            geometry.setPosition(converter.convertToPosition(operands["-pos"]));
            success = true;
        }

        if(operands.find("-w") != operands.end() && operands.find("-h") != operands.end())
        {
            geometry.setWidth(converter.convertToDimention(operands["-w"][0])); 
            geometry.setHeight(converter.convertToDimention(operands["-h"][0]));
            success = true;
        }

        return success;
    }


    bool ItemBuilder::trySetAttributes(std::unordered_map<std::string, std::vector<std::string>> operands, Data::Attributes& attributes)
    {
        bool success = false;

        Serialization::Converter converter;
        if(operands.find("-lcolor") != operands.end())
        {
            attributes.setHexLineColor(converter.convertToColor(operands["-lcolor"][0]));
            success = true;
        }

        if(operands.find("-fcolor") != operands.end())
        {
            attributes.setHexFillColor(converter.convertToColor(operands["-fcolor"][0]));
            success = true;
        }

        if(operands.find("-lwidth") != operands.end())
        {
            attributes.setLineWidth(std::stod(operands["-lwidth"][0]));
            success = true;
        }

        if(operands.find("-lstyle") != operands.end())
        {
            attributes.setLineType(converter.convertToLineType(operands["-lstyle"][0]));
            success = true;
        }

        if(operands.find("-text") != operands.end())
        {
            std::string concatenated;
            for(const auto& text : operands["-text"])
            {
                concatenated += text + " ";
            }
            attributes.setText(concatenated);
            success = true;
        }

        if(operands.find("-tcolor") != operands.end())
        {
            attributes.setHexTextColor(converter.convertToColor(operands["-tcolor"][0]));
            success = true;
        }

        if(operands.find("-fontsize") != operands.end())
        {
            attributes.setFontSize(converter.convertToID(operands["-fontsize"][0]));
            success = true;
        }

        return success;

    }



    std::shared_ptr<ItemBase> ItemBuilder::getItem() const
    {
        return item;
    }
}
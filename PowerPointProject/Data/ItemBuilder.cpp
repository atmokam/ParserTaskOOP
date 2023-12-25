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
        App::Application& application = *App::Application::getInstance();
        std::shared_ptr<IDocument> document = application.getDirector()->getDocument();
        Attributes defaultAttributes;
        Renderer::Type type;
        Serialization::Converter converter;

        item = std::make_shared<ItemLeaf>();
        defaultAttributes  = document->getDefaultAttributes();
        type = Renderer::Type{converter.convertToType(operands["-name"][0])};
        item->setType(type);
        item->setID(document->getIDGenerator().generateID());
            
        Geometry newGeometry;
        Attributes newAttributes; 

        trySetGeometry(operands, newGeometry);
        
        newAttributes.setHexLineColor((operands.find("-lcolor") != operands.end()) ? 
        converter.convertToColor(operands["-lcolor"][0]) : defaultAttributes.getHexLineColor().value());

        newAttributes.setHexFillColor((operands.find("-fcolor") != operands.end()) ?
        converter.convertToColor(operands["-fcolor"][0]) : defaultAttributes.getHexFillColor().value());
        
        newAttributes.setLineWidth((operands.find("-lwidth") != operands.end()) ? 
        std::stod(operands["-lwidth"][0]) : defaultAttributes.getLineWidth().value());
        
        newAttributes.setLineType((operands.find("-lstyle") != operands.end())? 
        converter.convertToLineType(operands["-lstyle"][0]) : defaultAttributes.getLineType().value());

        std::string concatenated;
        for(const auto& text : operands["-text"])
        {
            concatenated += text + " ";
        }

        newAttributes.setText((operands.find("-text") != operands.end()) ?
        concatenated : defaultAttributes.getText().value());

        newAttributes.setHexTextColor((operands.find("-tcolor") != operands.end()) ?
        converter.convertToColor(operands["-tcolor"][0]) : defaultAttributes.getHexTextColor().value());

        newAttributes.setFontSize((operands.find("-fontsize") != operands.end()) ?
        converter.convertToID(operands["-fontsize"][0]) : defaultAttributes.getFontSize().value());

        item->setAttributes(newAttributes);
        item->setGeometry(newGeometry);
        
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
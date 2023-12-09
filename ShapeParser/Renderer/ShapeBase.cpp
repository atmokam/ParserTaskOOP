#include "ShapeBase.hpp"
#include "Data/ItemBase.hpp"
#include "Data/ItemAttributes.hpp"
#include <vector>

ShapeBase::ShapeBase(std::shared_ptr<ItemBase> item) : item(item) {}

void ShapeBase::print(std::ostream& stream) 
{
    recursivePrintHandler(stream, item);
    
}

void ShapeBase::recursivePrintHandler(std::ostream& stream, const std::shared_ptr<ItemBase>& item) 
{
    if(auto leaf = std::dynamic_pointer_cast<ItemLeaf>(item))  
    {
        leafPrintHandler(stream, leaf);
        return;
    }
    else if(auto group = std::dynamic_pointer_cast<ItemGroup>(item))
    {
        for(auto& [_, subItem]: *group)
        {
            recursivePrintHandler(stream, subItem);
        }
    }

} 

void ShapeBase::leafPrintHandler(std::ostream& stream, const std::shared_ptr<ItemLeaf>& leaf) 
{
    stream << "Shape: ";
    stream << leaf->getType() << std::endl;
    stream << "---Geometry---" << std::endl;
    stream << "Position: ";
    stream << leaf->getGeometry().getPosition().value() << std::endl;
    stream << "Height: ";
    stream << leaf->getGeometry().getHeight().value() << std::endl;
    stream << "Width: ";
    stream << leaf->getGeometry().getWidth().value() << std::endl;
    stream << "---Attributes---" << std::endl;
    stream << "FillColor: ";
    stream << leaf->getAttributes().getHexFillColor().value() << std::endl;
    stream << "LineColor: ";
    stream << leaf->getAttributes().getHexLineColor().value() << std::endl;
    stream << "LineWidth: ";
    stream << leaf->getAttributes().getLineWidth().value() << std::endl;
    stream << "LineType: ";
    stream << leaf->getAttributes().getLineType().value() << std::endl;
}


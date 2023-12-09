#include "ShapeBase.hpp"
#include "ItemBase.hpp"
#include <vector>

ShapeBase::ShapeBase(std::shared_ptr<ItemBase> item) : item(item) {}

void ShapeBase::print(std::ostream& stream) 
{
    recursivePrintHandler(stream, item);
    
}

void ShapeBase::recursivePrintHandler(std::ostream& stream, const std::shared_ptr<ItemBase>& item) {
    if(auto leaf = std::dynamic_pointer_cast<ItemLeaf>(item))
    {
        leafPrintHandler(stream, leaf);
        return;
    }
    else if(auto group = std::dynamic_pointer_cast<ItemGroup>(item))
    {
        for(auto& [_, item]: *group)
        {
            recursivePrintHandler(stream, item);
        }
    }

}

void ShapeBase::leafPrintHandler(std::ostream& stream, const std::shared_ptr<ItemLeaf>& leaf) {
    stream << "Shape: " << leaf->getType() << std::endl;
    stream << "---Geometry---" << std::endl;
    stream << "Position: " << leaf->getGeometry().getPosition() << std::endl;
    stream << "Height: " << leaf->getGeometry().getHeight() << std::endl;
    stream << "Width: " << leaf->getGeometry().getWidth() << std::endl;
    stream << "---Attributes---" << std::endl;
    stream << "FillColor: " << leaf->getAttributes().getHexFillColor() << std::endl;
    stream << "LineColor: " << leaf->getAttributes().getHexLineColor() << std::endl;
    stream << "LineWidth: " << leaf->getAttributes().getLineWidth() << std::endl;
    stream << "LineType: " << leaf->getAttributes().getLineType() << std::endl;
}


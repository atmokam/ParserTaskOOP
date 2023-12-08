#include "ShapeBase.hpp"
#include "ItemBase.hpp"
#include <vector>

ShapeBase::ShapeBase(std::shared_ptr<ItemBase> item) : item(item) {}

void ShapeBase::print(std::ostream& stream) 
{
    Geometry geometry = item->getGeometry();
    if(auto group = std::dynamic_pointer_cast<ItemGroup>(item)){
        stream << "Group: " << group->getID() << std::endl;
        
        for(auto& child : *group){
            // if(auto subGroup = std::dynamic_pointer_cast<ItemGroup>(child.second)){
            //     // a function is needed to recursevly print the group
            // }
            stream << child.second->getID();
            stream << child.second->getAttributes();
            stream << child.second->getGeometry();
            stream << child.second->getType(); // add type to itemGroup as Type::Group
        }
    } 
    
}


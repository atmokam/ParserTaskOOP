#include "IDGenerator.hpp"
#include <algorithm>
namespace Data 
{
    IDGenerator::IDGenerator()
    {
        ids = {};
    }

    ID IDGenerator::generateID()
    {
        ID newID = (ids.empty()) ? 0 : getMaximumID() + 1;
        addID(newID);
        return newID;
    }

    void IDGenerator::addID(ID id)
    {
        ids.push_back(id);
    }

    void IDGenerator::removeID(ID id)
    {
        auto it = std::find(ids.begin(), ids.end(), id);
        if(it != ids.end())
            ids.erase(it);
    }

    std::vector<ID> IDGenerator::getIDs() const
    {
        return ids;
    }

    ID IDGenerator::getMaximumID() const
    {
        if(ids.empty())
            return 0;
        return ids.back();
    }

    void IDGenerator::setIDs(const std::vector<ID> ids)
    {
        this->ids = ids;
    }

}
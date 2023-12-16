#include "IDGenerator.hpp"

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


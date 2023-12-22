#ifndef IDGENERATOR_HPP
#define IDGENERATOR_HPP

#include <vector>


namespace Data
{
    using ID = int;

    class IDGenerator {
        std::vector<int> ids;
    public:
        IDGenerator();
        ID generateID();
        void addID(ID id);
        void removeID(ID id);
        std::vector<ID> getIDs() const;
        void setIDs(const std::vector<ID> ids);
        ID getMaximumID() const;
    };
}

#endif
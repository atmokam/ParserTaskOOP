#ifndef ITEMBUILDER_HPP
#define ITEMBUILDER_HPP

#include <memory>
#include <unordered_map>
#include <string>

#include "ItemBase.hpp"

namespace Data
{
    class ItemBuilder 
    {
        std::shared_ptr<Data::ItemBase> item = nullptr;

    public:
        ItemBuilder(std::shared_ptr<Data::ItemBase> item);
        ItemBuilder() =default;

        void buildItemLeaf(std::unordered_map<std::string, std::vector<std::string>>& operands);

        bool trySetAttributes(std::unordered_map<std::string, std::vector<std::string>> operands, Data::Attributes& attributes);
        bool trySetGeometry(std::unordered_map<std::string, std::vector<std::string>> operands, Data::Geometry& geometry);

        void setDefaultAttributes(std::unordered_map<std::string, std::vector<std::string>> operands, Data::Attributes& attributes);
        void setDefaultGeometry(std::unordered_map<std::string, std::vector<std::string>> operands, Data::Geometry& geometry);
        std::shared_ptr<Data::ItemBase> getItem() const;
    };
}
#endif 
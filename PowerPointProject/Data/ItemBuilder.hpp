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
        void changeExistingItem(std::unordered_map<std::string, std::vector<std::string>>& operands);
        std::shared_ptr<Data::ItemBase> getItem() const;
    };
}
#endif 
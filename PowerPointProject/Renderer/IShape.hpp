#ifndef ISHAPE_HPP
#define ISHAPE_HPP

#include <memory>

class ItemBase;

class IShape {
public:
    virtual std::shared_ptr<IShape> clone(std::shared_ptr<ItemBase> item) = 0;
}; 


#endif
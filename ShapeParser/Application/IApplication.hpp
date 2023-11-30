#ifndef IAPPLICATION_HPP
#define IAPPLICATION_HPP

#include <string>
#include <memory>

#include "Include/IController.hpp"
#include "Include/IDirector.hpp"

class IApplication {
public:
    virtual void run(int count, char* args[]) = 0;
    virtual void buildApplication() = 0;
    virtual std::shared_ptr<IDirector>& getDirector() = 0;
};

#endif
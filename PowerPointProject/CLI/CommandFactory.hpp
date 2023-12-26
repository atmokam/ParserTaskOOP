#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP

#include <memory>
#include <string>
#include "Command.hpp"

namespace CLI 
{
    class CommandFactory 
    {
    public:
        std::shared_ptr<Command> createCommand(std::string input);
    };
}

#endif
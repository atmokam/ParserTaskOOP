#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP

#include <memory>
#include <string>


namespace CLI 
{
    class Command;
    class CommandFactory 
    {
    public:
        std::shared_ptr<Command> createCommand(std::string input);
    };
}

#endif
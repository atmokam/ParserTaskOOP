#ifndef COMMANDHISTORY_HPP
#define COMMANDHISTORY_HPP

#include <vector>
#include <string>
#include <iostream>
#include <memory>

namespace CLI {

    class Command;

    class CommandHistory 
    {
        std::vector<std::shared_ptr<Command>> history;
        int index;
    public:
        CommandHistory();
        void add(std::shared_ptr<Command>& command);
        void up();
        void down();
        std::shared_ptr<Command>& getCurrent();
    };
}

#endif
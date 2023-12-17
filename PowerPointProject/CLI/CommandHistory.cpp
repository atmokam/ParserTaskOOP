#include "CommandHistory.hpp"    
#include <sstream>
namespace CLI {
    
    CommandHistory::CommandHistory() : index(-1) {}

    void CommandHistory::add(std::shared_ptr<Command>& command) 
    {
        history.push_back(command);
        ++index;
    }

    void CommandHistory::up() 
    {
        if(index > 0)
            --index;
    }

    void CommandHistory::down() 
    {
        if(index < history.size() - 1)
            --index;
    }

    std::shared_ptr<Command>& CommandHistory::getCurrent()
    {
        return history[index];
    }

}

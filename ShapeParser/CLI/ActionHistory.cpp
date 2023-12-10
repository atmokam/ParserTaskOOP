#include "ActionHistory.hpp"    
#include <sstream>

ActionHistory::ActionHistory() : index(-1) {}

void ActionHistory::add(std::istream& action) 
{
    std::string line;
    std::getline(action, line);
    history.push_back(line);
    index++;
}

void ActionHistory::up() 
{
    if(index > 0)
        index--;
}

void ActionHistory::down() 
{
    if(index < history.size() - 1)
        index++;
}

std::stringstream ActionHistory::getCurrent() 
{
    std::stringstream stream;
    stream << history[index];
    return stream;
}
#ifndef ACTIONHISTORY_HPP
#define ACTIONHISTORY_HPP

#include <vector>
#include <string>

class ActionHistory{
    std::vector<std::string> history;
    int index;
public:
    ActionHistory();
    void add(std::string action);
    std::string up();
    std::string down();
    std::string getCurrent();
};

#endif
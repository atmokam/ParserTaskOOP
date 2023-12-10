#ifndef ACTIONHISTORY_HPP
#define ACTIONHISTORY_HPP

#include <vector>
#include <string>
#include <iostream>

class ActionHistory{
    std::vector<std::string> history;
    int index;
public:
    ActionHistory();
    void add(std::istream& action);
    void up();
    void down();
    std::stringstream getCurrent();
};

#endif
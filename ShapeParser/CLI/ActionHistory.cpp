#include "ActionHistory.hpp"    

ActionHistory::ActionHistory() : index(-1) {}

void ActionHistory::add(std::string action){
    index++;
    history.push_back(action);
}

std::string ActionHistory::up(){
    if(index < 0){
        return "";
    }
    return history.at(index--);
}

std::string ActionHistory::down(){
    if(index >= history.size() - 1){
        return "";
    }
    return history.at(++index);
}

std::string ActionHistory::getCurrent(){
    if(index < 0){
        return "";
    }
    return history.at(index);
}

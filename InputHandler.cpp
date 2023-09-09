#include <iostream>
#include <sstream>
#include "ExitSignalException.hpp"
#include "InputHandler.hpp"


InputHandler::InputHandler(const std::vector<std::string>& args) : args(args) {}

InputHandler::InputHandler() { 
    std::string input, arg;
    getline(std::cin, input);
    std::stringstream iss(input);
    
    while(iss >> arg) {
        args.push_back(arg);
    }
}

std::vector<std::string> InputHandler::getArgs() const noexcept {
    return args;
}

bool InputHandler::exitCalled() const {
    if(args.size() == 1 && args[0] == "exit") {
        return true;
    }
    return false;
}

void InputHandler::exit() const {
    throw ExitSignalException();
}
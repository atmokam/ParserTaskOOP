#ifndef COMMAND_REGISTRY_HPP
#define COMMAND_REGISTRY_HPP

#include <string>
#include <unordered_set>
#include <algorithm>

class CommandRegistry {
    CommandRegistry() = delete;
    ~CommandRegistry() = delete;

    static std::unordered_set<std::string> modifiers;

    static std::unordered_set<std::string> commands ;

    static std::unordered_set<std::string> operands ;

public:

    static bool isNumber(const std::string& s) {
        char* end = nullptr;
        strtod(s.c_str(), &end);
        return end != s.c_str() && *end == '\0';
    }

    static bool isBoolean(const std::string& s) {
        return s == "true" || s == "false";
    }

    static bool commandFind(std::string token){ // if modifier and command and operand, or command and operand
        return (modifiers.find(token) != modifiers.end() || commands.find(token) != commands.end() || operands.find(token) != operands.end() || isNumber(token) || isBoolean(token))  ;
    }
};

std::unordered_set<std::string> CommandRegistry::modifiers = {
    "create", "remove"
};

std::unordered_set<std::string> CommandRegistry::commands = {
    "add", "sub", "mul", "div", "exit"
};

    
std::unordered_set<std::string> CommandRegistry::operands = {
    "-left", "-right", "-ops"
};

#endif
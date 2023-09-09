#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <vector>
#include <string>

class InputHandler {
private:
    std::vector<std::string> args;
public:
    InputHandler(const std::vector<std::string>& args);
    InputHandler(const std::istream& iss);
    InputHandler();
    ~InputHandler() = default;
    std::vector<std::string> getArgs() const noexcept;
    bool exitCalled() const;
    void runtimeInput() const;
    void exit() const;
};

#endif
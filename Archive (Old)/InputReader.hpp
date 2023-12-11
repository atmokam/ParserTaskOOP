#ifndef INPUTREADER_HPP
#define INPUTREADER_HPP

#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class InputReader {
private:
    std::vector<std::string> commandsVector;
    const std::string path;
public:
    InputReader(const std::string& args);
    void readInput();
    ~InputReader() = default;
    std::vector<std::string> getCommands() const noexcept;
};

#endif
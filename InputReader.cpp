#include "InputReader.hpp"

InputReader::InputReader(const std::string& args) : path(args) {}

void InputReader::readInput() {
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        commandsVector.push_back(line);
    }
}

std::vector<std::string> InputReader::getCommands() const noexcept {
    return commandsVector;
}


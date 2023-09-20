#include "Accumulator.hpp"

Accumulator::Accumulator(std::string textGotten) : text(textGotten){}

void Accumulator::accumulate() {
    std::string token;
    std::istringstream iss(text);
    while (iss >> token) {
        tokens.push_back(token);
    }
}

std::vector<std::string> Accumulator::getTokens() const noexcept {
    return tokens;
}


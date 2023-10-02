#ifndef ACCUMULATOR_HPP
#define ACCUMULATOR_HPP

#include <string>
#include <vector>
#include <sstream>

class Accumulator {
private:
    std::vector<std::string> tokens;
    std::string text;
public:
    Accumulator(std::string textGotten);
    ~Accumulator() = default;
    void accumulate();
    std::vector<std::string> getTokens() const noexcept;
};

#endif
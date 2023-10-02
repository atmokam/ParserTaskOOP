#ifndef PROGRAMEXECUTER_HPP
#define PROGRAMEXECUTER_HPP

#include <vector>
#include <string>
#include <iostream>

#include "InputReader.hpp"
#include "Accumulator.hpp"
#include "Parser.hpp"



class ProgramExecuter {
    const std::vector<std::string>& args;
public:
    ProgramExecuter(const std::vector<std::string>& args);
    ~ProgramExecuter() = default;
    void execute();

};
    

#endif
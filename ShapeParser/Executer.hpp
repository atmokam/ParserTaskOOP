#ifndef EXECUTER_HPP
#define EXECUTER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Parser.hpp"

class Executer
{
    std::ifstream stream;
    std::istream& input;
public:
    Executer() = default;
    Executer(int count, char* args[]);
    void runProgram();
    static std::ifstream buildStream(int count, char* args[]);

    
};

#endif 
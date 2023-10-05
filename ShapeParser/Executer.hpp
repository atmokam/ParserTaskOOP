#ifndef EXECUTER_HPP
#define EXECUTER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>


#include "Parser.hpp"
#include "Slide.hpp"

class Executer
{
    std::ifstream stream;
    std::istream& input;
    std::shared_ptr<Slide> slide;
public:
    Executer() = default;
    Executer(int count, char* args[], std::shared_ptr<Slide> slide);
    void runProgram();
    static std::ifstream buildStream(int count, char* args[]);

    
};

#endif 
#ifndef EXECUTER_HPP
#define EXECUTER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>


#include "Document.hpp"
#include "Parser.hpp"
#include "View.hpp" 

class Executer
{
    std::ifstream stream;
    std::istream& input;
    std::shared_ptr<Document> document;
    std::shared_ptr<View> view;
public:
    Executer() = default;
    Executer(int count, char* args[]); 
    void runProgram();
    static std::ifstream buildStream(int count, char* args[]);

    
};

#endif 
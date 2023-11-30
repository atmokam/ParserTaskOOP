#ifndef CLIController_HPP
#define CLIController_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>


#include "Parser.hpp"
#include "IController.hpp"


class CLIController : public IController {
    std::ifstream stream;
    std::istream& input;
    
public:
    CLIController() = default;
    CLIController(int count, char* args[]); 
    void runProgram() override;
    static std::ifstream buildStream(int count, char* args[]);
    
};

#endif 
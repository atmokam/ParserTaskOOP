#ifndef CLIController_HPP
#define CLIController_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>


#include "Data/Document.hpp"
#include "Parser.hpp"
#include "Data/View.hpp" 
#include "Interfaces/IController.hpp"


class CLIController : public IController {
    std::ifstream stream;
    std::istream& input;
    
public:
    CLIController() = default;
    CLIController(int count, char* args[]); 
    void runProgram() override;
    static std::ifstream buildStream(int count, char* args[]);
    void buildController() override;
    
};

#endif 
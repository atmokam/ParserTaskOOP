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
#include "Interfaces/IController.hpp"


class CLIController : public IController {
    std::ifstream stream;
    std::istream& input;
    std::shared_ptr<Director> director; // i might need to pass this to guicontroller(that's why a sharedptr), still a thing to think about
    
public:
    CLIController() = default;
    CLIController(int count, char* args[]); 
    void runProgram() override;
    static std::ifstream buildStream(int count, char* args[]);
    void buildController() override;
    
};

#endif 
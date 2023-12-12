#ifndef CLIController_HPP
#define CLIController_HPP

#include <istream>
#include <string>


#include "IController.hpp"
#include "CommandHistory.hpp"


class CLIController : public IController {
    std::istream& input;
    
public:
    CLIController() = default;
    CLIController(std::istream& input); 
    void runCommand(std::istream& input);
    void runProgram() override;
    
};

#endif 
#ifndef CLIController_HPP
#define CLIController_HPP

#include <istream>
#include <string>


#include "IController.hpp"
#include "CommandHistory.hpp"


class CLIController : public IController {
    std::istream& input;
    std::ostream& output;
public:
    CLIController() = default;
    CLIController(std::istream& input, std::ostream& output); 
    void runCommand(std::istream& input);
    std::ostream& getOutputStream() const override;
    std::istream& getInputStream() const override;
    void runProgram() override;
    
};

#endif 
#include "CLI/Controller.hpp"
#include "Parser.hpp"
#include "Validator.hpp"
#include "Command.hpp"
#include "Application/Application.hpp"

#include <iostream>



CLIController::CLIController(std::istream& stream) : input(stream){}

void CLIController::runProgram() {
    Application& application = Application::getInstance();  
    while (!application.isExitCalled()) 
    {
        runCommand(input);
    }
}

void CLIController::runCommand(std::istream& input)
{
    Parser oParser(input);
    std::shared_ptr<Command> pCmd = oParser.parse();
    
    pCmd->execute();
}




// exit command should be handled like all other commands,
// moreover it should ask user about unsaved changes & etc...

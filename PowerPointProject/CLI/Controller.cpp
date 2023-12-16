#include "CLI/Controller.hpp"
#include "Parser.hpp"
#include "Validator.hpp"
#include "Command.hpp"
#include "Application/Application.hpp"

#include <iostream>



CLIController::CLIController(std::istream& input, std::ostream& output) : input(input), output(output) {}

void CLIController::runProgram() {
    App::Application& application = App::Application::getInstance();  
    while (!application.isExitCalled()) 
    {
        runCommand(input);
    }
}

void CLIController::runCommand(std::istream& input) // also needed for command history
{
    Parser oParser(input);
    std::shared_ptr<Command> pCmd = oParser.parse();
    if(pCmd == nullptr)
        return;
    pCmd->execute();
}

std::ostream& CLIController::getOutputStream() const
{
    return output;
}

std::istream& CLIController::getInputStream() const
{
    return input;
}

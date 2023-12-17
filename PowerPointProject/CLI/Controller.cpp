#include "CLI/Controller.hpp"
#include "Parser.hpp"
#include "Validator.hpp"
#include "Command.hpp"
#include "Application/Application.hpp"

#include <iostream>

namespace CLI {

    Controller::Controller(std::istream& input, std::ostream& output) : input(input), output(output) {}

    void Controller::runProgram() {
        App::Application& application = App::Application::getInstance();  
        while (!application.isExitCalled()) 
        {
            runCommand(input);
        }
    }

    void Controller::runCommand(std::istream& input) // also needed for command history
    {
        Parser oParser(input);
        std::shared_ptr<Command> pCmd = oParser.parse();
        if(pCmd == nullptr)
            return;
        pCmd->execute();
    }

    std::ostream& Controller::getOutputStream() const
    {
        return output;
    }

    std::istream& Controller::getInputStream() const
    {
        return input;
    }
}
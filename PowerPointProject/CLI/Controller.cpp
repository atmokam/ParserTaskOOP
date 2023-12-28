#include "CLI/Controller.hpp"
#include "Parser.hpp"
#include "Validator.hpp"
#include "Command.hpp"
#include "Application/Application.hpp"

#include <iostream>

namespace CLI {

    Controller::Controller(): commandFactory(std::make_shared<CommandFactory>())
    {}

    void Controller::runCommand(std::istream& input) 
    {
        Parser oParser(input, commandFactory);
       
        std::shared_ptr<Command> pCmd = oParser.parse();

        if(pCmd == nullptr)
        {
            output << oParser.getErrorLog().str();
            return;
        }
        pCmd->execute();
    }

    std::stringstream& Controller::getOutputStream()
    {
        return output;
    }

}

    
    // void Controller::runProgram() {
    //     App::Application& application = *App::Application::getInstance(); 
      
    //     while (!application.isExitCalled()) 
    //     {
    //         runCommand(input);
    //     }
    // }
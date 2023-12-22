#ifndef CLICONTROLLER_HPP
#define CLICONTROLLER_HPP

#include <iostream>
#include <string>
#include <sstream>


#include "IController.hpp"
#include "CommandHistory.hpp"//parsed cmd and string
namespace CLI {

    class Controller : public IController {
        std::stringstream output;
    public:
        Controller() = default;
        void runCommand(std::istream& input);
        std::stringstream& getOutputStream() override;
        //std::istream& getInputStream() const override;
        //void runProgram() override;
        
    };
}

#endif 
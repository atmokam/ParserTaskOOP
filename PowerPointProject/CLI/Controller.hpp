#ifndef CLICONTROLLER_HPP
#define CLICONTROLLER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <memory>


#include "CommandFactory.hpp"

namespace CLI {

    class Controller  {
        std::stringstream output;
        std::shared_ptr<CommandFactory> commandFactory;
    public:
        Controller();
        void runCommand(std::istream& input);
        std::stringstream& getOutputStream();
    };
}

#endif 
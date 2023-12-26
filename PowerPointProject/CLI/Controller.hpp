#ifndef CLICONTROLLER_HPP
#define CLICONTROLLER_HPP

#include <iostream>
#include <string>
#include <sstream>


#include "IController.hpp"

namespace CLI {

    class Controller : public IController {
        std::stringstream output;
    public:
        Controller() = default;
        void runCommand(std::istream& input);
        std::stringstream& getOutputStream() override;
        
        
    };
}

#endif 
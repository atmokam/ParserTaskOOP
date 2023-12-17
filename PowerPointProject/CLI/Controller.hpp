#ifndef CLICONTROLLER_HPP
#define CLICONTROLLER_HPP

#include <istream>
#include <string>


#include "IController.hpp"
#include "CommandHistory.hpp"
namespace CLI {

    class Controller : public IController {
        std::istream& input;
        std::ostream& output;
    public:
        Controller() = default;
        Controller(std::istream& input, std::ostream& output); 
        void runCommand(std::istream& input);
        std::ostream& getOutputStream() const override;
        std::istream& getInputStream() const override;
        void runProgram() override;
        
    };
}

#endif 
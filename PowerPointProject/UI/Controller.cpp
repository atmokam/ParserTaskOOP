#include "Controller.hpp"
#include <fstream>
#include <QDebug>
#include "CLI/Controller.hpp"

namespace UI
{    
    Controller::Controller(std::ifstream& input, QWidget* parent): QWidget(parent)
    {
        controller = std::make_unique<CLI::Controller>();
        if(input.is_open())
            while(input.peek() == std::ifstream::traits_type::eof()) // for file input
            {
                controller->runCommand(this->input);
                output << controller->getOutputStream().str();
            }

    }

    Controller::~Controller()
    {

    }

    void Controller::runCommand(std::istream& input)
    {
        controller->runCommand(input);
        
        output << controller->getOutputStream().str();

    }

    std::stringstream& Controller::getOutputStream()
    {
        return output;
    }
}
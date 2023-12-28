#include "Controller.hpp"
#include <fstream>
#include <QDebug>

namespace UI
{    
    Controller::Controller(std::ifstream& input, std::shared_ptr<CLI::Controller> cliController, QWidget* parent):
    QWidget(parent), controller(cliController)
    {
        if(input.is_open())
            while(input.peek() == std::ifstream::traits_type::eof()) // for file input
            {
                controller.lock()->runCommand(this->input);
                output << controller.lock()->getOutputStream().str();
            }

    }

    Controller::~Controller()
    {

    }

    void Controller::runCommand(std::istream& input)
    {
        controller.lock()->runCommand(input);
        
        output << controller.lock()->getOutputStream().str();
        controller.lock()->getOutputStream().str({});

    }

    std::stringstream& Controller::getOutputStream()
    {
        return output;
    }
}
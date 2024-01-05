#include "Controller.hpp"
#include <fstream>
#include <QDebug>

namespace UI
{    
    Controller::Controller(std::ifstream& input, std::shared_ptr<CLI::Controller> cliController, QWidget* parent):
    QWidget(parent), controller(cliController)
    {
        if(input.is_open())
        {
            std::string line;
            while(std::getline(input, line)) // for file input
            {
                std::istringstream ss(line);
                controller.lock()->runCommand(ss);
                output << controller.lock()->getOutputStream().str();
            }
        }

    }

    Controller::~Controller()
    {

    }

    void Controller::runCommand(std::istream& input)
    {
        controller.lock()->runCommand(input);
        
        output << controller.lock()->getOutputStream().str();
        controller.lock()->getOutputStream().str({}); // empties cli::controller out stream

    }

    std::stringstream& Controller::getOutputStream()
    {
        return output;
    }
}
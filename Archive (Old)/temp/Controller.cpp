#include "Controller.hpp"
#include "CLI/Controller.hpp"

Controller::Controller(QWidget* parent)
    : QWidget(parent), controller(std::make_unique<CLI::Controller>(std::cin))
{
}

Controller::~Controller()
{

}

void Controller::runCommand(std::istream& input)
{
    controller->runCommand(input);
    
    output << controller->getOutputStream().rdbuf();

}

std::stringstream& Controller::getOutputStream()
{
    return output;
}

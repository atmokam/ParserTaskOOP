#ifndef UICONTROLLER_HPP
#define UICONTROLLER_HPP

#include "CLI/Controller.hpp"
#include <memory>
#include <istream>
#include <ostream>
#include <string>
#include <sstream>
#include <QWidget>


namespace UI
{
    class Controller : public QWidget
    {
        Q_OBJECT

    public:
        Controller(std::ifstream& input, std::shared_ptr<CLI::Controller> cliController, QWidget* parent = nullptr);
        virtual ~Controller();

        void runCommand(std::istream& input);
        std::stringstream& getOutputStream();
        
    private:
        std::weak_ptr<CLI::Controller> controller;
        std::stringstream input; //file
        std::stringstream output;
    };
}
#endif
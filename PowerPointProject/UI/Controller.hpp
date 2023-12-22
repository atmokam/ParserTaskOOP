#ifndef UICONTROLLER_HPP
#define UICONTROLLER_HPP

#include "CLI/Controller.hpp"
#include <memory>
#include <istream>
#include <ostream>
#include <string>
#include <sstream>
#include "CLI/Controller.hpp"
#include <QWidget>

class Controller : public QWidget
{
    Q_OBJECT

public:
    Controller(std::ifstream& input, QWidget* parent = nullptr);
    virtual ~Controller();

    void runCommand(std::istream& input);
    std::stringstream& getOutputStream();
    
private:
    std::unique_ptr<CLI::Controller> controller;
    std::stringstream input;//fstream
    std::stringstream output;
};

#endif
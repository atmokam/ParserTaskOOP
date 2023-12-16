#include "Application/Application.hpp"
#include <iostream>
#include <stdexcept>
#include <QApplication>

int main(int count, char* args[])
{
    try {
       // QApplication application(count, args);
        App::Application& app = App::Application::getInstance();
        app.run(count, args);
       // return application.exec();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

}
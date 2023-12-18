#include "Application/Application.hpp"
#include <iostream>
#include <stdexcept>
#include <QApplication>
#include <QWidget>

int main(int count, char* args[])
{
    App::Application application(count, args);
    try {
       
        return application.run(count, args);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    application.quit();
}
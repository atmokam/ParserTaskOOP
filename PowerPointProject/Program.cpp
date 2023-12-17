#include "Application/Application.hpp"
#include <iostream>
#include <stdexcept>
#include <QApplication>
#include <QWidget>

int main(int count, char* args[])
{
    try {
        App::Application application(count, args);
       
        return application.run(count, args);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

}
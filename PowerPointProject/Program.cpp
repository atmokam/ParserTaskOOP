#include "Application/Application.hpp"
#include <iostream>
#include <stdexcept>
#include <QApplication>
#include <QWidget>
#include "UI/MainWindow.hpp"

int main(int count, char* args[])
{
    try {
        App::Application application(count, args);
        UI::MainWindow* window = new UI::MainWindow();
        window->show();
        
        return application.exec();
        
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

}
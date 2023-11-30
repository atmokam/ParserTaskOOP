#include "Application/Application.hpp"
#include <iostream>
#include <stdexcept>

int main(int count, char* args[])
{
    try {
        Application& app = Application::getInstance();
        app.run(count, args);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

}
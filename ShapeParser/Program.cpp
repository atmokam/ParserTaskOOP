#include "CLI/Controller.hpp"
#include <iostream>
#include <stdexcept>

int main(int count, char* args[])
{
    try {
        CLIController controller(count, args);
        controller.runProgram();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

}
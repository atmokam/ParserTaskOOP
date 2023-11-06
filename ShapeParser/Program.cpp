#include "CLI/Executer.hpp"
#include <iostream>
#include <stdexcept>

int main(int count, char* args[])
{
    try {
        Executer executer(count, args);
        executer.runProgram();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

}
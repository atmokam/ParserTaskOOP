#include "Executer.hpp"
#include <iostream>
#include <stdexcept>

int main(int count, char* args[])
{
    try {
        std::shared_ptr<Slide> slide = std::make_shared<Slide>();
        Executer executer(count, args, slide);
        executer.runProgram();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

}
#include <iostream>
#include <string>
#include <vector>

#include "ProgramExecuter.hpp"
#include "ExitSignalException.hpp"
#include "InputHandler.hpp"
#include "Tokenizer.hpp"

int main(int argc, char *argv[]) {
    std::vector<std::string> args(argv + 1, argv + argc);
    try{
        
        ProgramExecuter programExecuter;
        
    } catch (const ExitSignalException& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
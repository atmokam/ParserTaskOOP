#include "ProgramExecuter.hpp"

int main(int argc, char *argv[]) {
    std::vector<std::string> args(argv + 1, argv + argc);
    try{
        ProgramExecuter programExecuter;
        
    } catch (const ExitSignalException& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
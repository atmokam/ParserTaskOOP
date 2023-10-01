#include "Executer.hpp"

Executer::Executer(int count, char* args[]) : stream(buildStream(count, args)), input(stream.is_open() ? stream : std::cin) { }


std::ifstream Executer::buildStream(int count, char* args[]) {
    
    std::ifstream stream;
    if(args[1] == nullptr)
        return stream;
    else if (std::string(args[1]) == "-filename") 
        stream.open(args[2]);
    return stream;

}

void Executer::runProgram() {
    Parser parser;
   
    std::string line;
    while(getline(input, line) && line != "exit") {
        parser.parse(line);            
    }
    
    
    //parser.getCommand()->execute();

}
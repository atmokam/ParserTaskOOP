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
   
    std::string word;
    while(input >> word && word != "exit") {
        
        if(input.peek() != '\n')
            parser.parse(word);
         else {
            parser.parse(word);
            if(!Validator::validateCommand(parser.command)) {
                throw std::invalid_argument("Invalid command: " + parser.command->getName());
            }
            //parser.getCommand()->execute();
            parser.reset();
        }
    }
///test
    
//
    //parser.getCommand()->execute();

}


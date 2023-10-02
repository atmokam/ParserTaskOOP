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
    while(input >> line) {
        
        if(input.peek() != '\n')
            parser.parse(line);
         else {
            parser.parse(line);
            //parser.getCommand()->execute();
            parser.reset();
        }
    }
///test
    std::unordered_map<std::string, std::vector<std::string>> operands = parser.command->getOperands();
    for(auto operand : operands) {
        std::cout << operand.first << ": ";
        for(auto value : operand.second) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
//
    //parser.getCommand()->execute();

}
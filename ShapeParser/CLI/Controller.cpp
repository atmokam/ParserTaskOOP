#include "CLI/Controller.hpp"

CLIController::CLIController(int count, char* args[]) : stream(buildStream(count, args)), input(stream.is_open() ? stream : std::cin) {
    director = std::make_shared<Director>();
}

std::ifstream CLIController::buildStream(int count, char* args[]) {
    
    std::ifstream stream;
    if(args[1] == nullptr)
        return stream;
    else if (std::string(args[1]) == "-filename") 
        stream.open(args[2]);
    return stream;

}

// TODO: add trim method for trailing whitespaces

void CLIController::runProgram() {
    Parser parser;
    
    std::string word;
    while(input >> word && word != "exit") { 
        
        if(input.peek() == '\n' || input.peek() == EOF){
            parser.parse(word);
            if(!Validator::validateCommand(parser.getCommand())) {
                throw std::invalid_argument("Invalid command: " + parser.getCommand()->getName());
            }
            parser.getCommand()->execute(director);
            parser.reset();
        } else {
            parser.parse(word);
        }
    }

}

void CLIController::buildController() {
    std::cout << "CLIController" << std::endl;
}
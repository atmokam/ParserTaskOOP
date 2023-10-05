#include "Executer.hpp"

Executer::Executer(int count, char* args[], std::shared_ptr<Slide> slide) : stream(buildStream(count, args)), input(stream.is_open() ? stream : std::cin), slide(slide) { }


std::ifstream Executer::buildStream(int count, char* args[]) {
    
    std::ifstream stream;
    if(args[1] == nullptr)
        return stream;
    else if (std::string(args[1]) == "-filename") 
        stream.open(args[2]);
    return stream;

}

// TODO: add trim method for trailing whitespaces

void Executer::runProgram() {
    Parser parser;
    
    std::string word;
    while(input >> word && word != "exit") {
        
        if(input.peek() == '\n' || input.peek() == EOF){
            parser.parse(word);
            if(!Validator::validateCommand(parser.command)) {
                throw std::invalid_argument("Invalid command: " + parser.command->getName());
            }
            parser.command->execute(slide);
            parser.reset();
        } else {
            parser.parse(word);
        }
    }

}


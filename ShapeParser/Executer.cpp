#include "Executer.hpp"

Executer::Executer(int count, char* args[]) : stream(buildStream(count, args)), input(stream.is_open() ? stream : std::cin), document(std::make_shared<Document>()), view(std::make_shared<View>(document)) { }


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
            if(!Validator::validateCommand(parser.getCommand())) {
                throw std::invalid_argument("Invalid command: " + parser.getCommand()->getName());
            }
            parser.getCommand()->execute(document, view);
            parser.reset();
        } else {
            parser.parse(word);
        }
    }

}


#include "CLI/Controller.hpp"
#include "Parser.hpp"
#include "Validator.hpp"
#include "Command.hpp"


// Line is too long, it makes program reading incoinvinient
// command line arguments should be handled by the Application, it is not the job of controller, 
// Instead controller need tpo get its inpiut stream as argument
CLIController::CLIController(int count, char* args[]) : stream(buildStream(count, args)), input(stream.is_open() ? stream : std::cin) {}

std::ifstream CLIController::buildStream(int count, char* args[]) {
    // This function belongs to the appliation
    std::ifstream stream;
    if(args[1] == nullptr)
        return stream;
    else if (std::string(args[1]) == "-filename") 
        stream.open(args[2]);
    return stream;

}

void CLIController::runProgram() {
    Parser parser;
    
    std::string word;
    // Reading a word from the input is the task of the tokenizer
    // Controller shouldn't read itself anything
    while(input >> word && word != "exit") {
        // exit command should be handled like all other commands,
        // moreover it should ask user about unsaved changes & etc...
        
        if(input.peek() == '\n' || input.peek() == EOF){
            // Ill formed parsing, parser gets input stream as argument or in its constructor and thats it! 
            // All this staff should happen inside the parser, parse method should return command object
            parser.parse(word);
            if(!Validator::validateCommand(parser.getCommand())) {
                throw std::invalid_argument("Invalid command: " + parser.getCommand()->getName());
            }
            parser.getCommand()->execute();
            parser.reset();
        } else {
            parser.parse(word);
        }
    }

}

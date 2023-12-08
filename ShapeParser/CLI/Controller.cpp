#include "CLI/Controller.hpp"
#include "Parser.hpp"
#include "Validator.hpp"
#include "Command.hpp"
#include "Application/Application.hpp"



CLIController::CLIController(std::istream& stream) : input(stream){}

void CLIController::runProgram() {
    Application& application = Application::getInstance();  
    while (!application.isExitCalled()) 
    {
        runCommand(input);
    }
}

void CLIController::runCommand(std::istream& input)
{
    Parser oParser(input);
    std::shared_ptr<Command> pCmd = oParser.parse();
    
    pCmd->execute();
}
















// void CLIController::runProgram() {
    
    
//     // Reading a word from the input is the task of the tokenizer
//     // Controller shouldn't read itself anything
//     while(input >> word && word != "exit") {
//         // exit command should be handled like all other commands,
//         // moreover it should ask user about unsaved changes & etc...
        
//         if(input.peek() == '\n' || input.peek() == EOF){
//             // Ill formed parsing, parser gets input stream as argument or in its constructor and thats it! 
//             // All this staff should happen inside the parser, parse method should return command object
//             parser.parse(word);
//             if(!Validator::validateCommand(parser.getCommand())) {
//                 throw std::invalid_argument("Invalid command: " + parser.getCommand()->getName());
//             }
//             parser.getCommand()->execute();
//             parser.reset();
//         } else {
//             parser.parse(word);
//         }
//     }

// }
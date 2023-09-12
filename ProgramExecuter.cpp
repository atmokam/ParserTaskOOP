#include "ProgramExecuter.hpp"


ProgramExecuter::ProgramExecuter(const std::vector<std::string>& args) { // for argument list
    InputHandler inputHandler(args);
    if (inputHandler.exitCalled()) {
        inputHandler.exit();
    }
    Validator validator(inputHandler.getArgs());
    if (!validator.isValid()) {
       throw std::invalid_argument("Invalid input");
    }
    
    Tokenizer tokenizer(inputHandler.getArgs()); 
    Parser parser(tokenizer.getTokens());
    OutputHandler outputHandler;
    outputHandler.printResult(parser.getResult());
    
}

ProgramExecuter::ProgramExecuter() { // for runtime input
    InputHandler inputHandler;
    if (inputHandler.exitCalled()) {
        inputHandler.exit();
    }
    Validator validator(inputHandler.getArgs());
    if (!validator.isValid()) {
       throw std::invalid_argument("Invalid input");
    }

    Tokenizer tokenizer(inputHandler.getArgs()); 
    Parser parser(tokenizer.getTokens());
    OutputHandler outputHandler;
    outputHandler.printResult(parser.getResult());
    
}
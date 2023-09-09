#include "ProgramExecuter.hpp"


ProgramExecuter::ProgramExecuter(const std::vector<std::string>& args) { // for argument list
    InputHandler inputHandler(args);
    if (inputHandler.exitCalled()) {
        inputHandler.exit();
    }
    
    Tokenizer tokenizer(args);
    //Parser parser(tokenizer.getTokens());
    //OutputHandler outputHandler(parser.getResult());
}

ProgramExecuter::ProgramExecuter() { // for runtime input
    InputHandler inputHandler;
    if (inputHandler.exitCalled()) {
        inputHandler.exit();
    }
    
    Tokenizer tokenizer(inputHandler.getArgs()); 
    std::cout << tokenizer.getTokens().first << std::endl; // tester
    std::cout << tokenizer.getTokens().second[0] << std::endl;
    std::cout << tokenizer.getTokens().second[1] << std::endl; // tester
    //Parser parser(tokenizer.getTokens());
    //OutputHandler outputHandler(parser.getResult());
}
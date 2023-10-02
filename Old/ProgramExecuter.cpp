#include "ProgramExecuter.hpp"



ProgramExecuter::ProgramExecuter(const std::vector<std::string>& args) : args(args) { }


void ProgramExecuter::execute() {
    InputReader inputReader(args[0]);
    inputReader.readInput();
    std::vector<std::string> commands = inputReader.getCommands();

    for(auto& command : commands) {
        Accumulator accumulator(command);
        accumulator.accumulate();
       
        Parser parser(accumulator.getTokens());
        parser.parse();

        // SemanticValidator semanticValidator(parser.getCommandAST());
        // semanticValidator.validate();
        // if(semanticValidator.isValid() && !semanticValidator.isQueued()) {
        //     Evaluator evaluator(parser.getCommandAST());
        //     evaluator.evaluate();
        //     OutputWriter outputWriter(evaluator.getResult());
        //     outputWriter.printResult();
        // }
    }
}
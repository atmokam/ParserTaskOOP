#include "Parser.hpp"

// parser does partial validation, checks the sequence for the structure <commandName> <operand> <value>, 
// also checks that two operands dont follow each other, eg. add -name -w

void Parser::parse(std::string input){
    std::vector<std::string> tokens = Accumulator::accumulate(input);
    std::string commandName = "", prevOperand = "", prevToken = "";

    for(auto token : tokens){
        if(commandName == "" && Validator::isName(token)){
            command = createCommand(token);
            commandName = token;
            prevToken = token;
        }
        else if(commandName != "" && (prevOperand != prevToken) && Validator::isOperand(token, commandName)){
            command->addOperandToOperands(token);
            prevOperand = token;
            prevToken = token;
        }
        else if(commandName != "" && prevOperand != "" && Validator::isValue(token, prevOperand) ){
            command->addValueToOperands(token, prevOperand); // + , operand
            prevToken = token;
        }
        else {
            throw std::invalid_argument("Invalid input: " + token);
        }
    }
    //Validator::validateCommand(command); // checks against malformation, eg. missing operands

    


}


std::unique_ptr<Command> Parser::createCommand(std::string input){
    if(input == "add"){
        return std::make_unique<AddCommand>();
    }
    else if(input == "remove"){
        return std::make_unique<RemoveCommand>();
    }
    else if(input == "save"){
        return std::make_unique<SaveCommand>();
    }
    else if(input == "change"){
        return std::make_unique<ChangeCommand>();
    }
    else if(input == "load"){
        return std::make_unique<LoadCommand>();
    }
    else if(input == "display"){
        return std::make_unique<DisplayCommand>();
    }
    else if(input == "exit"){
        return std::make_unique<ExitCommand>();
    }
    else if(input == "list"){
        return std::make_unique<ListCommand>();
    }
    else {
        throw std::invalid_argument("Invalid command: " + input);
    }
}
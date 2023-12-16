#include <stdexcept>
#include <iostream>
#include "Parser.hpp"
#include "Command.hpp"
#include "Validator.hpp"

// parser does partial validation, checks the sequence for the structure <commandNameFlag> <operand> <value>, 
// also checks that two operands don't follow each other, eg. add -name -w

Parser::Parser(std::istream& inputStream) : inputStream(inputStream) {}

void Parser::skipSpaces()
{
    while(inputStream.peek() == ' ')
    {
        inputStream.get();
    }
    
}

bool Parser::IsNewLine(char c) const
{
    return c == '\n' || c == '\r' || c == EOF;
}

std::string Parser::getToken()
{
    std::string sToken = "";
    skipSpaces();

    if (!IsNewLine(inputStream.peek()))
        inputStream >> sToken; 
    
    else 
        inputStream.get();

    return sToken;
}


std::shared_ptr<Command> Parser::parse()                        
{
    Validator validator;
    std::string name = getToken();
    if(name.empty())
        return nullptr;
    
    std::shared_ptr<Command> command = createCommand(name); 
    if(!command)
        throw std::invalid_argument("Invalid command: " + name);

    command->setName(name);
    commandNameFlag = name;
    prevToken = name;
   
    std::string argument;
    do{  
        argument = getToken();
        if(argument.empty())
            break;
        processArgument(argument, command);

    } while(!argument.empty());

    if(!validator.validateCommand(command)) 
    {
        throw std::invalid_argument("Invalid syntax for command: " + command->getName());
    }

    return command;
    
}




void Parser::processArgument(std::string argument, std::shared_ptr<Command>& command){
    Validator validator;
    if(commandNameFlag != "" && (prevOperand != prevToken) && validator.isOperand(argument, commandNameFlag)){
        command->addOperandToOperands(argument);
        prevOperand = argument;
        prevToken = argument;
    }
    else if(commandNameFlag != "" && prevOperand != "" && validator.isValue(argument, prevOperand) ){
        command->addValueToOperands(argument, prevOperand); 
        prevToken = argument;
    }
    else {
        throw std::invalid_argument("Invalid input: " + argument);
    }
}




std::shared_ptr<Command> Parser::createCommand(std::string input){
    
    if(input == "add"){
        return std::make_shared<AddCommand>();
    }
    else if(input == "remove"){
        return std::make_shared<RemoveCommand>();
    }
    else if(input == "save"){
        return std::make_shared<SaveCommand>();
    }
    else if(input == "change"){
        return std::make_shared<ChangeCommand>();
    }
    else if(input == "load"){
        return std::make_shared<LoadCommand>();
    }
    else if(input == "display"){
        return std::make_shared<DisplayCommand>();
    }
    else if(input == "list"){
        return std::make_shared<ListCommand>();
    }
    else if(input == "next"){
        return std::make_shared<NextCommand>();
    }
    else if(input == "prev"){
        return std::make_shared<PrevCommand>();
    }
    else if(input == "undo"){
        return std::make_shared<UndoCommand>();
    }
    else if(input == "redo"){
        return std::make_shared<RedoCommand>();
    }
    else if (input == "exit"){
        return std::make_shared<ExitCommand>();
    }
    else if(input == "draw"){
        return std::make_shared<DrawCommand>();
    }
    else {
        return nullptr;
    }
}



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
    while(std::isspace(inputStream.peek()))
    {
        std::cout << inputStream.get();
    }
}

bool Parser::IsNewLine(char c) const
{
    return c == '\n' || c == '\r';
}

std::string Parser::getToken()
{
    std::string sToken;
    if (!IsNewLine(inputStream.peek()))
        inputStream >> sToken; 
    skipSpaces();
    return sToken;
}



// std::shared_ptr<Command> Parser::parse()
// {
//     std::string cmdName = getToken();

//     std::shared_ptr<Command> pCmd = createCommand(cmdName);
//     command->setName(cmdName);
//     commandNameFlag = cmdName;
//     prevToken = cmdName;

//     if (pCmd == nullptr)
//         throw std::invalid_argument("Invalid command: " + cmdName);

//     std::string token = getToken();
//     while (!token.empty())
//     {
//         if((prevOperand != prevToken) && validator.isOperand(token, commandNameFlag))
//         {
//             command->addOperandToOperands(token);
//             prevOperand = token;
//             prevToken = token;
//         }
//         else if(prevOperand != "" && validator.isValue(token, prevOperand))
//         {
//             command->addValueToOperands(token, prevOperand); 
//             prevToken = token;
//         }
//         else 
//         {
//             throw std::invalid_argument("Invalid input: " + token);
//         }

//         token = getToken();
//     }

//     return pCmd;     
// }





// the above one throws segfault, for now I will be using the modifed-old version, temporarily
// will get back to this when I'm done with the other tasks

std::shared_ptr<Command> Parser::parse()
{
    std::string token;
    std::shared_ptr<Command> command = nullptr;
    Validator validator;


    while(inputStream >> token) 
    {  
        if(inputStream.peek() == '\n' || inputStream.peek() == EOF)
        {
            processArgument(token, command);
            if(!validator.validateCommand(command)) 
            {
                throw std::invalid_argument("Invalid command: " + command->getName());
            }
            return command;
        } 
        else 
        {
            processArgument(token, command);
        }
        
    }
    return command;
    
}



void Parser::processArgument(std::string argument, std::shared_ptr<Command>& command){
    Validator validator;
    if(commandNameFlag == "" && validator.isName(argument)){
            command = createCommand(argument);
            command->setName(argument);
            commandNameFlag = argument;
            prevToken = argument;
        }
        else if(commandNameFlag != "" && (prevOperand != prevToken) && validator.isOperand(argument, commandNameFlag)){
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
    else {
        return nullptr;
    }
}



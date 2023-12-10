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
    std::string sToken;
    skipSpaces();

    if (!IsNewLine(inputStream.peek()))
        inputStream >> sToken; 
    else
        sToken = "";
    return sToken;
}



// the one below keeps entering the controller loop, even if the input is empty
// that's why i get a segfault. I'm not sure, but I think the >> operator handles this case that's why it stops 
// reading when the stream is empty, and so i get that waiting behaviour


// std::shared_ptr<Command> Parser::parse()                           // 2nd attempt
// {
//     std::shared_ptr<Command> command = nullptr;
//     Validator validator;

//     std::string token;
   
//     do {  
//         token = getToken();
//         if(token == "") break;
//         std::cout << token << std::endl;
//         processArgument(token, command);
//     } while(!token.empty());

//     if(!validator.validateCommand(command)) 
//     {
//         throw std::invalid_argument("Invalid commands: " + command->getName());
//     }


//     return command;
    
// }


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



#include <stdexcept>
#include <iostream>
#include "Parser.hpp"
#include "Command.hpp"
#include "Validator.hpp"
#include "CommandFactory.hpp"

// parser does partial validation, checks the sequence for the structure <commandNameFlag> <operand> <value>, 
// also checks that two operands don't follow each other, eg. add -name -w
namespace CLI {
    
    Parser::Parser(std::istream& inputStream, std::shared_ptr<CommandFactory> commandFactory) : inputStream(inputStream), 
    commandFactory(commandFactory) {}

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
        
        
        std::shared_ptr<Command> command = commandFactory->createCommand(name); 
       
        if(!command)
        {
            errorLog << "Invalid command name: " + name << std::endl;
            return nullptr;
        }

        command->setName(name);
        commandNameFlag = name;
        prevToken = name;
    
        std::string argument;
        do
        {  
            argument = getToken();
            if(argument.empty())
                break;
            processArgument(argument, command);

        } while(!argument.empty());

        if(!validator.validateCommand(command)) 
        {
            errorLog << "Invalid syntax for command: " + command->getName() << std::endl;
            return nullptr;
        }

        return command;
        
    }




    void Parser::processArgument(std::string& argument, std::shared_ptr<Command>& command)
    {
        Validator validator;
        if(commandNameFlag != "" && (prevOperand != prevToken) && validator.isOperand(argument, commandNameFlag))
        {
            command->addOperandToOperands(argument);
            prevOperand = argument;
            prevToken = argument;
        }
        else if(commandNameFlag != "" && prevOperand != "" && validator.isValue(argument, prevOperand))
        {
            command->addValueToOperands(argument, prevOperand); 
            prevToken = argument;
        }
        else 
        {
            errorLog << "Invalid argument: " + argument << std::endl;
            argument = "";
        }
        
    }

    std::stringstream& Parser::getErrorLog()
    {
        return errorLog;
    }



}
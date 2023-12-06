#include <stdexcept>
#include "Parser.hpp"
#include "Command.hpp"
#include "Validator.hpp"

// parser does partial validation, checks the sequence for the structure <commandName> <operand> <value>, 
// also checks that two operands dont follow each other, eg. add -name -w


     Parser::skipSpaces()
{
    whuile (isSpace(input.peek())
        input.get();
}

Token Parser::getTopken()
{
    std::string sToken;
    skipSpaces();
    if (!IsNewLine(input.peek()))
        input >> sToken; 
    returns Token;
}

void Parser::parse()
{
    Token cmdName = getToken();
    // Lookup[ commad
    pCmd = Factory->get(cmdName);
    if (cmd == nullptr)
        throw;

    Token argName = getToken();
    while (!argName.empty())
    {
        // Lookup argument

        argValue = getToken();
    }

    return pCmd;     
}



void Parser::parse(std::string token){
    
    if(commandName == "" && Validator::isName(token)){
        command = createCommand(token);
        command->setName(token);
        commandName = token;
        prevToken = token;
    }
    else if(commandName != "" && (prevOperand != prevToken) && Validator::isOperand(token, commandName)){
        command->addOperandToOperands(token);
        prevOperand = token;
        prevToken = token;
    }
    else if(commandName != "" && prevOperand != "" && Validator::isValue(token, prevOperand) ){
        command->addValueToOperands(token, prevOperand); 
        prevToken = token;
    }
    else {
        throw std::invalid_argument("Invalid input: " + token);
    }
    
}

void Parser::reset(){
    commandName = "";
    prevOperand = "";
    prevToken = "";
    command = nullptr;
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
    else {
        throw std::invalid_argument("Invalid command: " + input);
    }
}


std::shared_ptr<Command> Parser::getCommand() const { return command; }

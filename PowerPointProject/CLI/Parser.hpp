#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <memory>
#include <istream>

class Command;

class Parser {

    std::istream& inputStream;
    std::shared_ptr<Command> createCommand(std::string input);
    std::string commandNameFlag, prevOperand, prevToken; 

    bool IsNewLine(char c) const;
    void processArgument(std::string argument, std::shared_ptr<Command>& command);
    
public:
    Parser(std::istream& input);
    std::shared_ptr<Command> parse();
    void skipSpaces();
    std::string getToken();
    void reset();
};

#endif
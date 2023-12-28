#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <memory>
#include <istream>
#include <sstream>
#include "CommandFactory.hpp"

namespace CLI 
{    
    class Command;

    class Parser 
    {
        std::istream& inputStream;
        std::string commandNameFlag, prevOperand, prevToken; 
        std::stringstream errorLog;
        std::shared_ptr<CommandFactory> commandFactory;

        bool IsNewLine(char c) const;
        void processArgument(std::string& argument, std::shared_ptr<Command>& command);
        void skipSpaces();
        std::string getToken();
        
    public:
        std::stringstream& getErrorLog();
        Parser(std::istream& input, std::shared_ptr<CommandFactory> commandFactory);
        std::shared_ptr<Command> parse();
        
    };
}

#endif
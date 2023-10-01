#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

using ValueType = std::variant<double, std::string, std::vector<double>>; //Shape -> string, + Position

class Command {
protected:
    std::unordered_map<std::string, ValueType> operands;
public:

    
    virtual void execute() = 0;
    virtual void addOperandToOperands(std::string operand); 
    virtual void addValueToOperands(std::string value, std::string operand);// converts and adds
    

};

class AddCommand : public Command {
public:

    
    void execute() override;
};

class RemoveCommand : public Command {

public:
    
    void execute() override;
};

class DisplayCommand : public Command {
public:
    
    void execute() override;
};

class ChangeCommand : public Command {
public:
    
    void execute() override;
};

class SaveCommand : public Command {
public:
    
    void execute() override;
};

class LoadCommand : public Command {
public:
    
    void execute() override;
};

class ListCommand : public Command {
public:
    
    void execute() override;
};

class ExitCommand : public Command {
public:
    
    void execute() override;
};


#endif
#ifndef COMMAND_HPP
#define COMMAND_HPP

// I might need to add a group command for item grouping

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

class IApplication;
class Slide;
class Item;
class ItemLeaf;

using OperandsContainer = std::unordered_map<std::string, std::vector<std::string>>;


class Command {
protected:
    OperandsContainer operands;
    std::string name;
    IApplication& application;

public:
    Command();
    virtual void execute() = 0;
    virtual void addOperandToOperands(std::string operand); 
    virtual void addValueToOperands(std::string value, std::string operand); 

    std::string getName() const;
    void setName(std::string name);
    OperandsContainer getOperands() const;


};

class AddCommand : public Command {
    std::shared_ptr<ItemLeaf> createItem();
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

class NextCommand : public Command {
public:
    
    void execute() override;
};

class PrevCommand : public Command {
public:
    
    void execute() override;
};

class UndoCommand : public Command {
public:
    
    void execute() override;
};

class RedoCommand : public Command {
public:
    
    void execute() override;
};

class ExitCommand : public Command {
public:
    
    void execute() override;
};



#endif
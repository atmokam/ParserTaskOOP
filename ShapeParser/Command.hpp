#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include <iostream>
#include <memory>

#include "ItemAttributes.hpp"
#include "Item.hpp"
#include "Converter.hpp"

//using ValueType = std::variant<Position, Type, ID, BoundingRect, Color>;

class Command {
protected:
    std::unordered_map<std::string, std::vector<std::string>> operands;
    std::string name;
public:

    virtual void execute() = 0;
    virtual void addOperandToOperands(std::string operand); 
    virtual void addValueToOperands(std::string value, std::string operand); 

    std::string getName() const;
    void setName(std::string name);
    std::unordered_map<std::string, std::vector<std::string>> getOperands() const { return operands; }
};

class AddCommand : public Command {
public:
    
    void execute() override;
    std::shared_ptr<Item> createItem();
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
    
    void execute() override;  // should I have this?
};


#endif
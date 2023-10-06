#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <memory>
#include <fstream>

#include "ItemAttributes.hpp"
#include "Item.hpp"
#include "Converter.hpp"
#include "Slide.hpp"



class Command {
protected:
    std::unordered_map<std::string, std::vector<std::string>> operands;
    std::string name;

public:

    virtual void execute(std::shared_ptr<Slide> slide) = 0;
    virtual void addOperandToOperands(std::string operand); 
    virtual void addValueToOperands(std::string value, std::string operand); 

    std::string getName() const;
    void setName(std::string name);
    std::unordered_map<std::string, std::vector<std::string>> getOperands() const { return operands; }
};

class AddCommand : public Command {
public:
    
    void execute(std::shared_ptr<Slide> slide) override;
    std::shared_ptr<Item> createItem();
};

class RemoveCommand : public Command {

public:
    
    void execute(std::shared_ptr<Slide> slide) override;
    int getItemID() ;
};

class DisplayCommand : public Command {
public:
    
    void execute(std::shared_ptr<Slide> slide) override;
    void displayItem(std::shared_ptr<Item> item);
};

class ChangeCommand : public Command {
public:
    
    void execute(std::shared_ptr<Slide> slide) override;
};

class SaveCommand : public Command {
public:
    
    void execute(std::shared_ptr<Slide> slide) override;
};

class LoadCommand : public Command {
public:
    
    void execute(std::shared_ptr<Slide> slide) override;
};

class ListCommand : public Command {
public:
    
    void execute(std::shared_ptr<Slide> slide) override;
};



#endif
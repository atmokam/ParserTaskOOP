#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <memory>
#include <fstream>

#include "Data/Item.hpp" //
#include "Serialization/Converter.hpp" //
#include "Data/Document.hpp" //
#include "Serialization/SaveLoad.hpp" //
#include "Director/Director.hpp" //
#include "Director/Renderer.hpp" //
#include "Director/Actions.hpp" //
#include "Application/IApplication.hpp"
//#include "Application/Application.hpp"

class Application;

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
    std::shared_ptr<Item> createItem(const std::shared_ptr<Slide>& slide, const size_t currentSlideIndex);
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




#endif
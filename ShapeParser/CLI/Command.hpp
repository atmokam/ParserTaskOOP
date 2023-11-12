#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <memory>
#include <fstream>

#include "Data/Item.hpp"
#include "Serialization/Converter.hpp"
#include "Data/Document.hpp"
#include "Data/View.hpp"
#include "Serialization/SaveLoad.hpp"
#include "Director/Director.hpp"



class Command {
protected:
    std::unordered_map<std::string, std::vector<std::string>> operands;
    std::string name;

public:

    virtual void execute(std::shared_ptr<Director>& director) = 0;
    virtual void addOperandToOperands(std::string operand); 
    virtual void addValueToOperands(std::string value, std::string operand); 

    std::string getName() const;
    void setName(std::string name);
    std::unordered_map<std::string, std::vector<std::string>> getOperands() const;


};

class AddCommand : public Command {
public:
    
    void execute(std::shared_ptr<Director>& director) override;
};

class RemoveCommand : public Command {

public:
    
    void execute(std::shared_ptr<Director>& director) override;
};

class DisplayCommand : public Command {
public:
    
    void execute(std::shared_ptr<Director>& director) override;
    
};

class ChangeCommand : public Command {
public:
    
    void execute(std::shared_ptr<Director>& director) override;
};

class SaveCommand : public Command {
public:
    
    void execute(std::shared_ptr<Director>& director) override;
};

class LoadCommand : public Command {
public:
    
    void execute(std::shared_ptr<Director>& director) override;
};

class ListCommand : public Command {
public:
    
    void execute(std::shared_ptr<Director>& director) override;
    

};

class NextCommand : public Command {
public:
    
    void execute(std::shared_ptr<Director>& director) override;
};

class PrevCommand : public Command {
public:
    
    void execute(std::shared_ptr<Director>& director) override;
};

class UndoCommand : public Command {
public:
    
    void execute(std::shared_ptr<Director>& director) override;
};

class RedoCommand : public Command {
public:
    
    void execute(std::shared_ptr<Director>& director) override;
};




#endif
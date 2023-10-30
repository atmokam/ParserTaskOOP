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
#include "Document.hpp"
#include "View.hpp"



class Command {
protected:
    std::unordered_map<std::string, std::vector<std::string>> operands;
    std::string name;

public:

    virtual void execute(std::shared_ptr<Document> document, std::shared_ptr<View> view) = 0;
    virtual void addOperandToOperands(std::string operand); 
    virtual void addValueToOperands(std::string value, std::string operand); 

    std::string getName() const;
    void setName(std::string name);
    std::unordered_map<std::string, std::vector<std::string>> getOperands() const { return operands; }

    std::shared_ptr<Slide> getCurrentSlide(std::shared_ptr<Document> document, std::shared_ptr<View> view) const;
};

class AddCommand : public Command {
public:
    
    void execute(std::shared_ptr<Document> document, std::shared_ptr<View> view) override;
    std::shared_ptr<Item> createItem(std::shared_ptr<Slide> slide);
};

class RemoveCommand : public Command {

public:
    
    void execute(std::shared_ptr<Document> document, std::shared_ptr<View> view) override;
    int getItemID() ;
};

class DisplayCommand : public Command {
public:
    
    void execute(std::shared_ptr<Document> document, std::shared_ptr<View> view) override;
    
};

class ChangeCommand : public Command {
public:
    
    void execute(std::shared_ptr<Document> document, std::shared_ptr<View> view) override;
};

class SaveCommand : public Command {
public:
    
    void execute(std::shared_ptr<Document> document, std::shared_ptr<View> view) override;
    void saveToFile(std::ofstream& file, const std::unordered_map<int, std::shared_ptr<Item>>& items);
};

class LoadCommand : public Command {
public:
    
    void execute(std::shared_ptr<Document> document, std::shared_ptr<View> view) override;
    std::shared_ptr<Item> setItemAttribute(std::string_view file);
};

class ListCommand : public Command {
public:
    
    void execute(std::shared_ptr<Document> document, std::shared_ptr<View> view) override;
    

};

class NextCommand : public Command {
public:
    
    void execute(std::shared_ptr<Document> document, std::shared_ptr<View> view) override;
};

class PrevCommand : public Command {
public:
    
    void execute(std::shared_ptr<Document> document, std::shared_ptr<View> view) override;
};


void displayItem(std::shared_ptr<Item> item);


#endif
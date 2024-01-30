#include <algorithm>
#include <fstream>
#include "CLI/Validator.hpp"
#include "Command.hpp"
#include "Renderer/Shape/ShapeLibrary.hpp"

#include <iostream>



// operand quantity checking: 0 means no value, -1 means any number of values
namespace CLI {
    
    Validator::Validator()
    {
        valids = {
            {"add", {{"-name", 1}, {"-pos", -1}, {"-lcolor", 1}, {"-fcolor", 1}, {"-w", 1}, {"-h", 1}, {"-slide", 0}, {"-lwidth", 1}, {"-lstyle", 1}, {"-text", -1}, {"-tcolor", 1}, {"-fontsize", 1}}},
            {"remove", {{"-id", 1}, {"-slide", 0}}},
            {"change", {{"-id", 1}, {"-name", 1}, {"-pos", -1}, {"-lcolor", 1}, {"-fcolor", 1}, {"-w", 1}, {"-h", 1},  {"-lwidth", 1}, {"-lstyle", 1}, {"-text", -1}, {"-tcolor", 1}, {"-fontsize", 1}}},
            {"display", {{"-id", 1}}},
            {"list", {}},
            {"save", {{"-path", 1}, {"-filename", 1}}},
            {"load", {{"-path", 1}}}, 
            {"next", {}}, 
            {"prev", {}},
            {"undo", {}},
            {"redo", {}},
            {"exit", {{"-force", 0}}},
            {"draw", {{"-path", 1}, {"-filename", 1}}}
        };

        mandatoryOperands = {
            {"addSlide", {"-slide"}},
            {"addItem", {"-name", "-pos", "-w", "-h"}},
            {"addLine", {"-name", "-pos"}},
            {"removeSlide", {"-slide"}},
            {"removeItem", {"-id"}},
            {"change", {"-id"}},
            {"save", {"-path", "-filename"}},
            {"load", {"-path"}},
            {"draw", {"-path", "-filename"}}
        };

        

        styles = {
            "solid", "dashed", "dotted"
        };


    }


    bool Validator::validateCommand(const std::shared_ptr<Command>& commandToBeChecked) 
    { 
        if (!checkOperandQuantity(commandToBeChecked) || !checkMandatoryOperands(commandToBeChecked)) 
        {
            return false;
        }
        return true;
    }


    bool Validator::checkOperandQuantity(const std::shared_ptr<Command>& commandToBeChecked)
    {
        auto commandName = commandToBeChecked->getName();
        auto commandOperands = commandToBeChecked->getOperands();
        
        auto values = valids.at(commandName);

        for(const auto& [key, value] : commandOperands) 
        {
            auto validOperand = values.find(key);
            if(validOperand == values.end()) 
            {
                return false;
            }
            else if (validOperand != values.end())
            {
                if(validOperand->second == -1 || validOperand->second == value.size())
                    return true;
                else
                    return false;
            }
        }

        return true;
    }



    bool Validator::checkMandatoryOperands(const std::shared_ptr<Command>& commandToBeChecked) 
    {
        auto commandName = commandToBeChecked->getName();
        auto commandOperands = commandToBeChecked->getOperands();
        std::vector<std::string> mandatory;
        

        if (commandName == "add" && commandOperands.find("-slide") != commandOperands.end()) 
        {
            mandatory = mandatoryOperands.at("addSlide");
        } 
        else if (commandName == "add" && commandOperands.find("-name") != commandOperands.end()) 
        {
            if(commandOperands.at("-name")[0] == "line")
                mandatory = mandatoryOperands.at("addLine");
            else
                mandatory = mandatoryOperands.at("addItem");
        } 
        else if (commandName == "remove" && commandOperands.find("-slide") != commandOperands.end()) 
        {
            mandatory = mandatoryOperands.at("removeSlide");
        } 
        else if (commandName == "remove" && commandOperands.find("-id") != commandOperands.end()) 
        {
            mandatory = mandatoryOperands.at("removeItem");
        } 
        else if (mandatoryOperands.find(commandName) != mandatoryOperands.end()) 
        {
            mandatory = mandatoryOperands.at(commandName);
        }


        for (const auto& operand : mandatory) 
        {
            if (commandOperands.find(operand) == commandOperands.end()) 
            {
                return false;
            }
        }

        return true;
    }






    bool Validator::isName(const std::string& inputToBeChecked) 
    {
        return valids.find(inputToBeChecked) != valids.end();
    }

    bool Validator::isOperand(const std::string& inputToBeChecked, const std::string& commandName) 
    {
        auto validsForCommand = valids.at(commandName);
        return validsForCommand.find(inputToBeChecked) != validsForCommand.end();
    }

    bool Validator::isDouble(const std::string& inputToBeChecked) 
    {
        try {
            double number = std::stod(inputToBeChecked);
            return true;
        } catch (...) {
            return false;
        }
    }

    bool Validator::isHex(const std::string& inputToBeChecked) 
    {
        return inputToBeChecked.size() == 7 && inputToBeChecked[0] == '#' &&
        std::all_of(inputToBeChecked.begin() + 1, inputToBeChecked.end(), isxdigit);
    }

    bool Validator::isInteger(const std::string& inputToBeChecked) 
    {
        return std::all_of(inputToBeChecked.begin(), inputToBeChecked.end(), isdigit);
    }

    bool Validator::isPath(const std::string& inputToBeChecked) 
    { 
        std::ifstream file(inputToBeChecked);
        return file.good();
    }

    bool Validator::isFilename(const std::string& inputToBeChecked) 
    {
        return std::all_of(inputToBeChecked.begin(), inputToBeChecked.end(), isalnum);
    }

    bool Validator::isStyle(const std::string& inputToBeChecked) 
    {
        return std::find(styles.begin(), styles.end(), inputToBeChecked) != styles.end();
    }



    bool Validator::isValue(const std::string& inputToBeChecked, const std::string& operandName) 
    {
        if (operandName == "-name") {
            Renderer::ShapeLibrary shapeLibrary;
            return shapeLibrary.getType(inputToBeChecked) != Renderer::Type::None;

        } else if (operandName == "-id") {
            return isInteger(inputToBeChecked);

        } else if (operandName == "-pos") {
            return isDouble(inputToBeChecked);

        } else if (operandName == "-lcolor") {
            return isHex(inputToBeChecked);

        } else if (operandName == "-fcolor") {
            return isHex(inputToBeChecked);

        } else if (operandName == "-path") {
            return isPath(inputToBeChecked);

        } else if (operandName == "-w" || operandName == "-h") {
            return isDouble(inputToBeChecked);

        } else if (operandName == "-filename") {
            return isFilename(inputToBeChecked);
            
        } else if (operandName == "-slide") {
            return isInteger(inputToBeChecked);

        } else if (operandName == "-lwidth"){
            return isDouble(inputToBeChecked);

        } else if (operandName == "-lstyle"){
            return isStyle(inputToBeChecked);

        } else if (operandName == "-text") {
            return true;

        } else if(operandName == "-tcolor") {
            return isHex(inputToBeChecked);

        } else if(operandName == "-fontsize") {
            return isInteger(inputToBeChecked);
        }
        else {
            return false;
        }
    
    }

}
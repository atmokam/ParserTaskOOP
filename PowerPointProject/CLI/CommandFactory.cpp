#include "CommandFactory.hpp"
#include "Command.hpp"

namespace CLI
{
    std::shared_ptr<Command> CommandFactory::createCommand(std::string input)
    {
        
        if(input == "add")
        {
            return std::make_shared<AddCommand>();
        }
        else if(input == "remove")
        {
            return std::make_shared<RemoveCommand>();
        }
        else if(input == "save")
        {
            return std::make_shared<SaveCommand>();
        }
        else if(input == "change")
        {
            return std::make_shared<ChangeCommand>();
        }
        else if(input == "load")
        {
            return std::make_shared<LoadCommand>();
        }
        else if(input == "display")
        {
            return std::make_shared<DisplayCommand>();
        }
        else if(input == "list")
        {
            return std::make_shared<ListCommand>();
        }
        else if(input == "next")
        {
            return std::make_shared<NextCommand>();
        }
        else if(input == "prev")
        {
            return std::make_shared<PrevCommand>();
        }
        else if(input == "undo")
        {
            return std::make_shared<UndoCommand>();
        }
        else if(input == "redo")
        {
            return std::make_shared<RedoCommand>();
        }
        else if (input == "exit")
        {
            return std::make_shared<ExitCommand>();
        }
        else if(input == "draw")
        {
            return std::make_shared<DrawCommand>();
        }
        else 
        {
            return nullptr;
        }
    }
}
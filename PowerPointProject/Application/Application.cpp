#include <fstream>

#include "Application.hpp"
#include "CLI/Controller.hpp"
#include "Director/Director.hpp" 
#include "Include/IController.hpp"
#include "Include/IDirector.hpp"
#include "Data/Document.hpp"
#include "CLI/CommandHistory.hpp"

namespace App // application doesnt quit after exit is executed
{
    Application::Application(int count, char* args[]) : QApplication(count, args) {  }

    Application& Application::getInstance() 
    {
        return QApplication::instance(); //////////////////////
    }

    int Application::run(int count, char* args[]) 
    {
        buildApplication(count, args);
        controller->runProgram();
        return QApplication::exec();
        
    }


    void Application::buildApplication(int count, char* args[]) 
    {
        director = std::make_shared<Director>();
        document = std::make_shared<Document>();
        std::ifstream stream = buildStream(count, args);

        std::istream& input = stream.is_open() ? stream : std::cin;
        std::ostream& output = std::cout;

        controller = std::make_unique<CLIController>(input, output);
    }

    void Application::callExit() 
    {
        exitCalled = true;
        
    }

    bool Application::isExitCalled() const 
    {
        return exitCalled;
    }

    std::shared_ptr<IDirector> Application::getDirector() 
    {
        return director;
    }

    std::shared_ptr<IDocument> Application::getDocument() 
    {
        return document;
    }

    std::ifstream Application::buildStream(int count, char* args[]) 
    {
        std::ifstream stream;
        if(args[1] == nullptr)
            return stream;
        else if (std::string(args[1]) == "-filename") 
            stream.open(args[2]);
        return stream;

    }

    std::shared_ptr<IController> Application::getController() 
    {
        return controller;
    }
    

}
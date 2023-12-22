#include <fstream>
#include <iostream>
#include "Application.hpp"
#include "CLI/Controller.hpp"
#include "Director/Director.hpp" 
#include "Include/IController.hpp"
#include "Include/IDirector.hpp"
#include "Data/Document.hpp"
#include "CLI/CommandHistory.hpp"

namespace App 
{
    Application::Application(int &argc, char **argv) : QApplication(argc, argv) // This was the culprit, I had not noticed that there needed to be a & before int, that was the segfault reason
    {                                                                           // the GUI window now opens without problem
        director = std::make_shared<Director::Director>();
        document = std::make_shared<Data::Document>();
        std::ifstream input = buildStream(argc, argv);
        controller = std::make_unique<Controller>(input);
    }

    Application* Application::getInstance() 
    {
        return dynamic_cast<Application*>(QApplication::instance());
    }

    int Application::run(int count, char* args[]) 
    {
        buildApplication(count, args);
       // controller->runProgram();
        
    }

    void Application::quit() 
    {
       QApplication::quit();
    }


    void Application::buildApplication(int count, char* args[]) // remove this
    {
        director = std::make_shared<Director::Director>();
        document = std::make_shared<Data::Document>();
        std::ostream& output = std::cout;

     
    }

    void Application::callExit() 
    {
        exitCalled = true;
        
    }

    bool Application::isExitCalled() const 
    {
        return exitCalled;
    }

    std::shared_ptr<Director::Director::IDirector> Application::getDirector() 
    {
        return director;
    }

    std::shared_ptr<Data::IDocument> Application::getDocument() 
    {
        return document;
    }

    std::ifstream Application::buildStream(int& count, char* args[]) 
    {
        std::ifstream stream;
        
        if(args[1] == nullptr)
            return stream;

        else if (std::string(args[1]) == "-filename") 
        {
            stream.open(args[2]);
        }
        return stream;

    }

    std::shared_ptr<Controller> Application::getController() 
    {
        return controller;
    }
    
    Application::~Application() 
    {
       
    }

}
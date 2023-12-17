#include <fstream>

#include "Application.hpp"
#include "CLI/Controller.hpp"
#include "Director/Director.hpp" 
#include "Include/IController.hpp"
#include "Include/IDirector.hpp"
#include "Data/Document.hpp"
#include "CLI/CommandHistory.hpp"

namespace App // application stops, but doesnt quit after exit is executed (acc. to stackoverflow, there needs to be a window to quit, but there is none for now, so I guess that's why it doesn't quit)
{
    Application* Application::instance = nullptr;

    Application::Application(int count, char* args[]) : QApplication(count, args), file(buildStream(count, args)), input(file.is_open() ? file : std::cin)
    { 
        instance = this;
    }

    Application& Application::getInstance() 
    {
        if(instance == nullptr)
            throw std::runtime_error("Application has not been initialized");
        return *instance;
    }

    int Application::run(int count, char* args[]) 
    {
        buildApplication(count, args);
        controller->runProgram();
        return instance->exec(); 
    }

    void Application::quit() 
    {
        instance->quit();
    }


    void Application::buildApplication(int count, char* args[]) 
    {
        director = std::make_shared<Director::Director>();
        document = std::make_shared<Data::Document>();
        std::ostream& output = std::cout;

        controller = std::make_unique<CLI::Controller>(input, output);
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

    std::ifstream Application::buildStream(int count, char* args[]) 
    {
        std::ifstream stream;
        if(args[1] == nullptr)
            return stream;
        else if (std::string(args[1]) == "-filename") {
            stream.open(args[2]);
        }
        return stream;

    }

    std::shared_ptr<CLI::IController> Application::getController() 
    {
        return controller;
    }
    
    Application::~Application() 
    {
        quit();

    }

}
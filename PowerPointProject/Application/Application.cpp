#include <fstream>
#include <iostream>
#include "Application.hpp"
#include "Director/Director.hpp" 
#include "Data/Document.hpp"
#include "CLI/CommandHistory.hpp"

namespace App 
{
    Application::Application(int &argc, char **argv) : QApplication(argc, argv) // This was the cause, int needed to be a reference, but it wasn't and that was the segfault reason
    {                                                                           // the GUI window now opens without problem
        director = std::make_shared<Director::Director>();
        document = std::make_shared<Data::Document>();
        cliController = std::make_shared<CLI::Controller>();
        std::ifstream input = buildStream(argc, argv);
        controller = std::make_shared<UI::Controller>(input, cliController);
    }

    Application& Application::getInstance() 
    {
        return *static_cast<Application*>(QApplication::instance());
    }

    void Application::quit() 
    {
       QApplication::quit();
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
            std::cout << "filed"<< std::endl;
        }
        return stream;

    }

    std::shared_ptr<UI::Controller> Application::getController() 
    {
        return controller;
    }
    
    Application::~Application() 
    {
       
    }

}
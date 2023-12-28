#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Include/IApplication.hpp"

#include <fstream>

namespace App
{
    class Application: public IApplication, public QApplication {
    protected:
        std::shared_ptr<UI::Controller> controller;
        std::shared_ptr<CLI::Controller> cliController;
        std::shared_ptr<Director::IDirector> director; 
        std::shared_ptr<Data::IDocument> document;
        
    public:
        
        static Application& getInstance();
        
        void quit() override;
        static std::ifstream buildStream(int& count, char* args[]);

        std::shared_ptr<Director::IDirector> getDirector() override;
        std::shared_ptr<Data::IDocument> getDocument() override;
        std::shared_ptr<UI::Controller> getController() override;

        Application(int &argc, char **argv);
        ~Application();
       
    };
}

#endif
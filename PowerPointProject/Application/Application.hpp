#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>
#include "Include/IApplication.hpp"
#include "Include/IDirector.hpp"
#include "Include/IDocument.hpp"
#include "Include/IController.hpp"

// Why did I have to make this inherit from QApplication?

namespace App
{
    class Application: public IApplication, public QApplication {
        std::shared_ptr<IController> controller;
        std::shared_ptr<IDirector> director; 
        std::shared_ptr<IDocument> document;

        
        bool exitCalled = false;
    public:
        
        static Application& getInstance();
        bool isExitCalled() const;
        void callExit() override;
        int run(int count, char* args[]) override;
        void quit() override;
        void buildApplication(int count, char* args[]) override;
        std::ifstream buildStream(int count, char* args[]);
        std::shared_ptr<IDirector> getDirector() override;
        std::shared_ptr<IDocument> getDocument() override;
        std::shared_ptr<IController> getController() override;

        Application(int count, char* args[]);
        ~Application();
    private:
        static Application* instance;
    };
}

#endif
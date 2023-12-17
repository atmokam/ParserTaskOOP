#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>
#include "Include/IApplication.hpp"
#include "Include/IDirector.hpp"
#include "Include/IDocument.hpp"
#include "Include/IController.hpp"
#include <fstream>

// Why did I have to make this inherit from QApplication?

namespace App
{
    class Application: public IApplication, public QApplication {
        std::shared_ptr<CLI::IController> controller;
        std::shared_ptr<Director::IDirector> director; 
        std::shared_ptr<Data::IDocument> document;

        std::ifstream file;
        std::istream& input;
        
        bool exitCalled = false;
    public:
        
        static Application& getInstance();
        bool isExitCalled() const;
        void callExit() override;
        int run(int count, char* args[]) override;
        void quit() override;
        void buildApplication(int count, char* args[]) override;

        static std::ifstream buildStream(int count, char* args[]);

        std::shared_ptr<Director::IDirector> getDirector() override;
        std::shared_ptr<Data::IDocument> getDocument() override;
        std::shared_ptr<CLI::IController> getController() override;

        Application(int count, char* args[]);
        ~Application();
    private:
        static Application* instance;
    };
}

#endif
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>
#include "Include/IApplication.hpp"
#include "Include/IDirector.hpp"
#include "Include/IDocument.hpp"
#include "Include/IController.hpp"

namespace App
{
    class Application: public IApplication {
        std::unique_ptr<IController> controller;
        std::shared_ptr<IDirector> director; 
        std::shared_ptr<IDocument> document;

        bool documentModified = false;
        bool exitCalled = false;
    public:
        
        static Application& getInstance();
        bool isExitCalled() const;
        void callExit() override;
        void run(int count, char* args[]) override;
        void buildApplication() override;
        std::ifstream buildStream(int count, char* args[]);
        std::shared_ptr<IDirector> getDirector() override;
        std::shared_ptr<IDocument> getDocument() override;

        bool isDocumentModified() const override;
        void setDocumentModified(bool modified) override;

    private:
        Application();
    };
}

#endif
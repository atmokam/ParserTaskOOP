#ifndef IAPPLICATION_HPP
#define IAPPLICATION_HPP

#include <string>
#include <memory>
#include <QApplication>

#include "Include/IController.hpp"
#include "Include/IDocument.hpp"
#include "Include/IDirector.hpp"

namespace App
{

    class IApplication {
    public:
        virtual std::shared_ptr<Director::IDirector> getDirector() = 0;
        virtual std::shared_ptr<Data::IDocument> getDocument() = 0;
        virtual std::shared_ptr<CLI::IController> getController() = 0;
        virtual int run(int count, char* args[]) = 0;
        virtual void buildApplication(int count, char* args[]) = 0;
        virtual void callExit() = 0;
        virtual bool isExitCalled() const = 0;
        virtual void quit() = 0;
        
    };
    
}

#endif
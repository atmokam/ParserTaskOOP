#ifndef IAPPLICATION_HPP
#define IAPPLICATION_HPP

#include <string>
#include <memory>
#include <QApplication>

class IDirector;
class IDocument;
class IController;

namespace App
{

    class IApplication {
    public:
        virtual std::shared_ptr<IDirector> getDirector() = 0;
        virtual std::shared_ptr<IDocument> getDocument() = 0;
        virtual std::shared_ptr<IController> getController() = 0;
        virtual int run(int count, char* args[]) = 0;
        virtual void buildApplication(int count, char* args[]) = 0;
        virtual void callExit() = 0;
        virtual bool isExitCalled() const = 0;
        
    };
    
}

#endif
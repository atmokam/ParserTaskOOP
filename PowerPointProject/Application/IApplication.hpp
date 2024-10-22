#ifndef IAPPLICATION_HPP
#define IAPPLICATION_HPP

#include <memory>
#include <QApplication>

#include "UI/Controller.hpp"
#include "Include/IDocument.hpp"
#include "Include/IDirector.hpp"

namespace App
{

    class IApplication {
    public:
        virtual std::shared_ptr<Director::IDirector> getDirector() = 0;
        virtual std::shared_ptr<Data::IDocument> getDocument() = 0;
        virtual std::shared_ptr<UI::Controller> getController() = 0;
        
        virtual void quit() = 0;
        
    };
    
}

#endif
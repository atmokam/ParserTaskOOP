#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>

#include "Application/IApplication.hpp"

class IController;
class IDirector;



class Application: public IApplication {
    std::unique_ptr<IController> controller;
    std::shared_ptr<IDirector> director; // director has the document, I dont know whether that's a good idea or not
public:
    
    static Application& getInstance();
    void run(int count, char* args[]) override;
    void buildApplication() override;
    std::shared_ptr<IDirector>& getDirector() override;

private:
    Application();
};

#endif
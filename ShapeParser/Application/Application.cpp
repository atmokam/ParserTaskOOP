#include "Application.hpp"
#include "CLI/Controller.hpp"
#include "Director/Director.hpp" 
#include "Include/IController.hpp"
#include "Include/IDirector.hpp"
#include "Data/Document.hpp"


Application::Application() {
    buildApplication();
}

Application& Application::getInstance() {
    static Application instance;
    return instance;
}

void Application::run(int count, char* args[]) {

    director = std::make_shared<Director>();
    document = std::make_shared<Document>();
   
    std::ifstream stream = buildStream(count, args);

    controller = std::make_unique<CLIController>(stream.is_open() ? stream : std::cin);
    controller->runProgram();
}

void Application::buildApplication() {
    
    // setting up gui, probably
}

void Application::callExit() {
    exitCalled = true;
}

bool Application::isExitCalled() const {
    return exitCalled;
}

std::shared_ptr<IDirector> Application::getDirector() {
    return director;
}

std::shared_ptr<IDocument> Application::getDocument() {
    return document;
}

std::ifstream Application::buildStream(int count, char* args[]) {
   
    std::ifstream stream;
    if(args[1] == nullptr)
        return stream;
    else if (std::string(args[1]) == "-filename") 
        stream.open(args[2]);
    return stream;

}
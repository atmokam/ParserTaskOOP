#include "Application.hpp"
#include "CLI/Controller.hpp"
#include "Director/Director.hpp" 
#include "Include/IController.hpp"
#include "Include/IDirector.hpp"


Application::Application() {
    buildApplication();
}

Application& Application::getInstance() {
    static Application instance;
    return instance;
}

void Application::run(int count, char* args[]) {
    director = std::make_shared<Director>();
    // also you need to create blank document here, document also held by app
    // and process arguments, if path is specified automatically load the document
    controller = std::make_unique<CLIController>(count, args);
    controller->runProgram();
}

void Application::buildApplication() {
    // setting up gui, probably
}

std::shared_ptr<IDirector>& Application::getDirector() {
    return director;
}

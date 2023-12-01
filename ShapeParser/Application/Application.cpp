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
    controller = std::make_unique<CLIController>(count, args);
    controller->runProgram();
}

void Application::buildApplication() {
    // setting up gui, probably
}

std::shared_ptr<IDirector>& Application::getDirector() {
    return director;
}
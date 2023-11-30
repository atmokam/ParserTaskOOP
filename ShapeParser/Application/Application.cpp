#include "Application.hpp"
#include "Director/Director.hpp" // how can i solve the referncing of non-interface classes(i have to use std::make_shared)
#include "CLI/Controller.hpp"


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
    // setting up gui
}

std::shared_ptr<IDirector>& Application::getDirector() {
    return director;
}
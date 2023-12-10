#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>
#include "Include/IApplication.hpp"
#include "Include/IDirector.hpp"
#include "Include/IDocument.hpp"
#include "Include/IController.hpp"
#include "CLI/ActionHistory.hpp"


class Application: public IApplication {
    std::unique_ptr<IController> controller;
    std::shared_ptr<IDirector> director; 
    std::shared_ptr<IDocument> document;
    std::shared_ptr<ActionHistory> history;

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
    std::shared_ptr<ActionHistory> getHistory() const;

private:
    Application();
};

#endif
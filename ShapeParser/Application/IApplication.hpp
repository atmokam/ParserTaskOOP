#ifndef IAPPLICATION_HPP
#define IAPPLICATION_HPP

#include <string>
#include <memory>

class IDirector;
class IDocument;

class IApplication {
public:
    virtual std::shared_ptr<IDirector> getDirector() = 0;
    virtual std::shared_ptr<IDocument> getDocument() = 0;
    virtual void run(int count, char* args[]) = 0;
    virtual void buildApplication() = 0;
    
};

#endif
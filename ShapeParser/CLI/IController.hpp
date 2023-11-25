#ifndef ICONTROLLER_HPP
#define ICONTROLLER_HPP

class IController {
protected:
    virtual void runProgram() = 0;
    virtual void buildController() = 0;
};

#endif

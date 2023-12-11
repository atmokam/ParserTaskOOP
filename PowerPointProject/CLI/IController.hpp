#ifndef ICONTROLLER_HPP
#define ICONTROLLER_HPP

class IController {
public:
    virtual void runProgram() = 0;
    virtual ~IController() = default;
};

#endif

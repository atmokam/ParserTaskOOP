#ifndef ICONTROLLER_HPP
#define ICONTROLLER_HPP

class IController {
public:
    virtual void runProgram() = 0;
    virtual ~IController() = default;
    virtual std::ostream& getOutputStream() const = 0;
    virtual std::istream& getInputStream() const = 0;
};

#endif

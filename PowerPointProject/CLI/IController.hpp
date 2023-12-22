#ifndef ICONTROLLER_HPP
#define ICONTROLLER_HPP

namespace CLI 
{   
    class IController 
    {

    public:
        //virtual void runProgram() = 0;
        virtual ~IController() = default;
        virtual std::stringstream& getOutputStream() = 0;
        //virtual std::istream& getInputStream() const = 0;
    };
}

#endif
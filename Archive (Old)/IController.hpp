#ifndef ICONTROLLER_HPP
#define ICONTROLLER_HPP

namespace CLI 
{   
    class IController 
    {

    public:
        virtual ~IController() = default;
        virtual std::stringstream& getOutputStream() = 0;
    };
}

#endif
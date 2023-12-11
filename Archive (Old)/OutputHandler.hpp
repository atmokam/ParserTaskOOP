#ifndef OUTPUTHANDLER_HPP
#define OUTPUTHANDLER_HPP
   
#include <string>
#include <iostream>

class OutputHandler {
public:

    template<typename T>
    void printResult(const T& result) {
        std::cout << "result: " << result << std::endl;
    }
private:
    std::string result;
};

#endif 
#ifndef OUTPUTHANDLER_HPP
#define OUTPUTHANDLER_HPP

#include <string>

class OutputHandler {
public:
    OutputHandler(std::string result);
    void printResult();
private:
    std::string result;
};

#endif
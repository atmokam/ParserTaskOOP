#ifndef PROGRAMEXECUTER_HPP
#define PROGRAMEXECUTER_HPP
#include <vector>
#include <string>

class ProgramExecuter {
public:
    ProgramExecuter(const std::vector<std::string>& args);
    ProgramExecuter();
    ~ProgramExecuter() = default;
};

#endif
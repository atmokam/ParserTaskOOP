#ifndef PROGRAMEXECUTER_HPP
#define PROGRAMEXECUTER_HPP

#include "InputHandler.hpp"
#include "Tokenizer.hpp"
#include "Parser.hpp"


class ProgramExecuter {
public:
    ProgramExecuter(const std::vector<std::string>& args);
    ProgramExecuter();
    ~ProgramExecuter() = default;
};

#endif
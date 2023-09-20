#ifndef SYNTAXVALIDATOR_HPP
#define SYNTAXVALIDATOR_HPP

#include <string>
#include <vector>
#include <iostream>

class SyntaxValidator { 
private:
    std::vector<std::string> text;
    bool valid;
public:
    SyntaxValidator(std::vector<std::string> textGotten);
    ~SyntaxValidator() = default;
    void validate();
    bool isValid() const noexcept;
};

#endif
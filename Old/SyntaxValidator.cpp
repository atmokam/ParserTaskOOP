#include "SyntaxValidator.hpp"
#include "CommandRegistry.hpp"

SyntaxValidator::SyntaxValidator(std::vector<std::string> textGotten) : text(textGotten) {}

void SyntaxValidator::validate() {
    for(auto& token: text) // checks if token is in reg
        if(!CommandRegistry::commandFind(token)) {
            valid = false;
            std::cout << "-> " << token << std::endl;
            return;
        }
        
    valid = true;
}

bool SyntaxValidator::isValid() const noexcept {
    return valid;
}
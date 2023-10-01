#include "Accumulator.hpp"


std::vector<std::string> Accumulator::accumulate(std::string input){
    std::vector<std::string> tokens;
    
    std::stringstream ss(input);
    std::string token;
    while(ss >> token) {
        if(token.find(",") != std::string::npos)
            token = token.substr(0, token.find(",")); 
        tokens.push_back(token);
    }

    return tokens;
    
}


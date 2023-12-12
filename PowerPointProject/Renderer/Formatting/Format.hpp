#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <unordered_map>
#include <string>

class Format
{
    std::unordered_map<std::string, std::pair<double, double>> formatMap;
public:
    Format();
    std::pair<double, double> getFormat(const std::string& format); 
};


#endif
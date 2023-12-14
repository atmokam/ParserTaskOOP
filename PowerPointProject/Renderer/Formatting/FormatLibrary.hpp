#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <unordered_map>
#include <string>

class FormatLibrary
{
    std::unordered_map<std::string, std::pair<double, double>> formatMap;
public:
    FormatLibrary();
    std::pair<double, double> getFormat(const std::string& format); 
};


#endif
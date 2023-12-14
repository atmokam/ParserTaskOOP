#include "FormatLibrary.hpp"

FormatLibrary::FormatLibrary() 
{
    formatMap["A0"] = {46.8, 33.1}; // in inches
    formatMap["A1"] = {33.1, 23.4};
    formatMap["A2"] = {23.4, 16.5};
    formatMap["A3"] = {16.5, 11.7};
    formatMap["A4"] = {11.7, 8.3};
    formatMap["A5"] = {8.3, 5.8};
}

std::pair<double, double> FormatLibrary::getFormat(const std::string& format) 
{
    return formatMap.at(format);
}


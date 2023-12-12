#include "Format.hpp"

Format::Format() 
{
    formatMap["A0"] = {33.1, 46.8}; // in inches
    formatMap["A1"] = {23.4, 33.1};
    formatMap["A2"] = {16.5, 23.4};
    formatMap["A3"] = {11.7, 16.5};
    formatMap["A4"] = {8.3, 11.7};
    formatMap["A5"] = {5.8, 8.3};
}

std::pair<double, double> Format::getFormat(const std::string& format) 
{
    return formatMap[format];
}


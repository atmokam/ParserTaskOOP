#include "DimentionConverter.hpp"
#include "FormatLibrary.hpp"

namespace Renderer::Formatting
{
    DimentionConverter::DimentionConverter(double dpi) : dpi(dpi){} // default DPI set to 96

    int DimentionConverter::toPixels(double inches) const 
    {
        return static_cast<int>(inches * dpi);
    }

    double DimentionConverter::toInches(int pixels) const 
    {
        return static_cast<double>(pixels) / dpi;
    }
}
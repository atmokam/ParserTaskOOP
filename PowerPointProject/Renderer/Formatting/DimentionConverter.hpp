#ifndef DIMENTIONCONVERTER_HPP
#define DIMENTIONCONVERTER_HPP

#include <string>

namespace Renderer::Formatting
{
    class DimentionConverter {
    private:
        double dpi;

    public:
        DimentionConverter( double dpi = 96);

        int toPixels(double inches) const;

        double toInches(int pixels) const;
    };
}
#endif
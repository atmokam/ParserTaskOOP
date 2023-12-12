#ifndef DIMENTIONCONVERTER_HPP
#define DIMENTIONCONVERTER_HPP


class DimentionConverter {
private:
    double dpi;

public:
    DimentionConverter(double dpi = 96);

    int toPixels(double inches) const;

    double toInches(int pixels) const;
};

#endif
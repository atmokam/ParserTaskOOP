#ifndef QTCOVERTER_HPP
#define QTCOVERTER_HPP

#include <QPen>

class QtConverter {
public:
    Qt::PenStyle convertToQtPenStyle(const std::string& style);
};

#endif
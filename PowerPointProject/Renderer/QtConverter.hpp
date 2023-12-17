#ifndef QTCOVERTER_HPP
#define QTCOVERTER_HPP

#include <QPen>

namespace Renderer
{
    class QtConverter 
    {
    public:
        Qt::PenStyle convertToQtPenStyle(const std::string& style);
    };
}
#endif
#include "QtConverter.hpp"


namespace Renderer
{
    Qt::PenStyle QtConverter::convertToQtPenStyle(const std::string& style) {
        if(style == "solid")
        {
            return Qt::SolidLine;
        }
        else if(style == "dashed")
        {
            return Qt::DashLine;
        }
        else if(style == "dotted")
        {
            return Qt::DotLine;
        }
        else
        {
            return Qt::NoPen;
        }
    }
}
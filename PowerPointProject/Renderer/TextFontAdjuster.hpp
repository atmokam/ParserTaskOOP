#ifndef TEXTFONTADJUSTER_HPP
#define TEXTFONTADJUSTER_HPP

#include <QFont>
#include <QRect>
#include <QString>

namespace Renderer
{
    class TextFontAdjuster 
    {
    public:
        TextFontAdjuster() = default;
        void adjustFont(QFont& font, QRect& boundingRectangle,  const QString& text);
    };
}
#endif
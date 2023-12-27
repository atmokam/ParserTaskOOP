#include "TextFontAdjuster.hpp"
#include <QFontMetrics>

namespace Renderer
{
    void TextFontAdjuster::adjustFont(QFont& font, QRect& boundingRectangle, const QString& text)
    {
        int size = font.pointSize(); // in pixels

        QFontMetrics fontMetrics(font);

        QRect rectToFit = fontMetrics.boundingRect(boundingRectangle, Qt::TextWordWrap, text);

        if (rectToFit.height() < boundingRectangle.height() || rectToFit.width() < boundingRectangle.width())
            return;

        int step = -1;
        while (size > 1)
        {
            font.setPointSize(size + step);

            QFontMetrics fm(font);
            rectToFit = fm.boundingRect(boundingRectangle, Qt::TextWordWrap, text);

            size += step; 
            if (rectToFit.height() < boundingRectangle.height() || rectToFit.width() < boundingRectangle.width())
                break; 
            
        }

        font.setPointSize(size);
    }
}
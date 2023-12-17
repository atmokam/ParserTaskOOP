#include "TextFontAdjuster.hpp"
#include <QFontMetrics>

namespace Renderer
{
    int TextFontAdjuster::adjustFont(QFont& font, QRect& boundingRectangle, const QString& text)
    {
        int size = font.pointSize(); // in pixels

        QFontMetrics fontMetrics(font);

        QRect rectToFit = fontMetrics.boundingRect(boundingRectangle, Qt::TextWordWrap, text);

        int step = rectToFit.height() > boundingRectangle.height() ? -1 : 1;
        while (size > 1)
        {
            font.setPointSize(size + step);

            QFontMetrics fm(font);
            rectToFit = fm.boundingRect(boundingRectangle, Qt::TextWordWrap, text);

            if (step < 0) 
            { 
                size += step; 
                if (rectToFit.height() < boundingRectangle.height()) 
                    break; 
            } 
            else 
            { 
                size += step; 
                if (rectToFit.height() > boundingRectangle.height()) 
                    break; 
            }
        }

        font.setPointSize(size);
    }
}
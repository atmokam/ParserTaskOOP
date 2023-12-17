#ifndef IVISUALDISPLAYABLE_HPP
#define IVISUALDISPLAYABLE_HPP

class QPainter;



namespace Renderer
{
    
    namespace Formatting
    {
        class DimentionConverter;
    }

    class IVisualDisplayable {
    public:
        virtual void draw(QPainter& painter, Formatting::DimentionConverter& converter) = 0;
    };
}
#endif
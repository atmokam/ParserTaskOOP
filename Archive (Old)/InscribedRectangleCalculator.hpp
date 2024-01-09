#ifndef INNERRECTANGLECALCUALTOR_HPP
#define INNERRECTANGLECALCUALTOR_HPP

#include <memory>

class QRect;

namespace Renderer
{
    namespace Formatting
    {
        class DimentionConverter;
    }
    
    class ShapeBase;

    class InscribedRectangleCalculator
    {
    public:
        InscribedRectangleCalculator() = default;
        QRect calculateRectangle(std::shared_ptr<ShapeBase> shape, Formatting::DimentionConverter& converter);
    };

}
#endif
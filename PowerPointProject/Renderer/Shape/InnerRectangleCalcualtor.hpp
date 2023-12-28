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

    class InnerRectangleCalcualtor
    {
    public:
        InnerRectangleCalcualtor() = default;
        QRect calculateInnerRectangle(std::shared_ptr<ShapeBase> shape, Formatting::DimentionConverter& converter);
    };

}
#endif
#ifndef VISUALRENDERINGVISITOR_HPP
#define VISUALRENDERINGVISITOR_HPP

#include "Data/IVisitor.hpp"
#include <memory>
#include "Data/Slide.hpp"
#include "Shape/ShapeLibrary.hpp"
#include "Formatting/DimentionConverter.hpp"
#include <QPaintDevice>

namespace Renderer
{
    class VisualRenderingVisitor: public Data::IVisitor
    {
        std::shared_ptr<ShapeLibrary> shapeLibrary;    
        QPaintDevice& device;
        Formatting::DimentionConverter& converter;
    public:
        VisualRenderingVisitor(QPaintDevice& device, Formatting::DimentionConverter& converter);
        VisualRenderingVisitor() =default;
        //void draw(const std::shared_ptr<Data::Slide>& slide);
        void draw(const std::shared_ptr<Data::ItemBase>& item);
        virtual void visit(Data::ItemLeaf& item) override;
        virtual void visit(Data::ItemGroup& items) override;
    };
}

#endif
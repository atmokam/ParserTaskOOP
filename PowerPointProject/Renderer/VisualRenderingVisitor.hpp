#ifndef VISUALRENDERINGVISITOR_HPP
#define VISUALRENDERINGVISITOR_HPP

#include "Include/IItemVisitor.hpp"
#include <memory>
#include "Data/Slide.hpp"
#include "Shape/ShapeLibrary.hpp"
#include "Formatting/DimentionConverter.hpp"
#include <QPaintDevice>

namespace Renderer
{
    class VisualRenderingVisitor: public Data::IItemVisitor
    {
        std::shared_ptr<ShapeLibrary> shapeLibrary;    
        QPaintDevice& device;
        Formatting::DimentionConverter& converter;
    public:
        VisualRenderingVisitor(QPaintDevice& device, Formatting::DimentionConverter& converter);
        virtual void visit(Data::ItemLeaf& item) override;
        virtual void visit(Data::ItemGroup& items) override;

        void draw(const std::shared_ptr<Data::ItemBase>& item);
    };
}

#endif
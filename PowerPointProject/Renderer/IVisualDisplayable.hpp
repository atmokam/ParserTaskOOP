#ifndef IVISUALDISPLAYABLE_HPP
#define IVISUALDISPLAYABLE_HPP

class QPainter;
class DimentionConverter;

class IVisualDisplayable {
public:
    virtual void draw(QPainter& painter, DimentionConverter& converter) = 0;
};

#endif
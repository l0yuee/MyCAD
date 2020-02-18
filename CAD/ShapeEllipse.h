#ifndef SHAPEELLIPSE_H
#define SHAPEELLIPSE_H

#include "ShapeObject.h"

class ShapeEllipse : public ShapeObject
{
public:
    ShapeEllipse();
    ShapeEllipse(QPoint &begin, QPoint &end, QPen &pen, QBrush &brush);
    virtual ~ShapeEllipse() override;
    
    // ShapeObject interface
public:
    virtual void draw_shape(QPainter *painter) override;
    
    // ShapeObject interface
public:
    virtual bool is_selected(const QPoint &pos) override;
    
    // ShapeObject interface
public:
    virtual void draw_auxiliary(QPainter *painter) override;
    
    // ShapeObject interface
public:
    virtual TYPE get_type() const override;
};


class EllipseFactory : public ShapeFactory {
public:
    EllipseFactory() {}
    virtual ~EllipseFactory() override {}
    
    
    // ShapeFactory interface
public:
    virtual ShapeObject *create_shape() override;
    virtual ShapeObject *create_shape(QPoint &begin, QPoint &end, QPen &pen, QBrush &brush) override;
};

#endif // SHAPEELLIPSE_H

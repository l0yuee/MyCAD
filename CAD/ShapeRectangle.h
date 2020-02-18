#ifndef SHAPERECTANGLE_H
#define SHAPERECTANGLE_H

#include "ShapeObject.h"

class ShapeRectangle : public ShapeObject
{
public:
    ShapeRectangle();
    ShapeRectangle(QPoint &begin, QPoint &end, QPen &pen, QBrush &brush);
    virtual ~ShapeRectangle() override;
    
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

class RectangleFactory : public ShapeFactory {
public:
    RectangleFactory() {}
    virtual ~RectangleFactory() override {}
    
    
    // ShapeFactory interface
public:
    virtual ShapeObject *create_shape() override;
    virtual ShapeObject *create_shape(QPoint &begin, QPoint &end, QPen &pen, QBrush &brush) override;
};

#endif // SHAPERECTANGLE_H

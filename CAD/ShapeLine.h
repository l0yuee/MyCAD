#ifndef SHAPELINE_H
#define SHAPELINE_H

#include "ShapeObject.h"
#include <QPoint>
#include <QPen>
#include <QBrush>
#include <QPainter>

class ShapeLine : public ShapeObject
{
public:
    ShapeLine();
    ShapeLine(QPoint &begin, QPoint &end, QPen &pen, QBrush &brush);
    virtual ~ShapeLine() override;
    
    
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

class LineFactory : public ShapeFactory {
public:
    LineFactory() {}
    virtual ~LineFactory() override {}
    
    
    // ShapeFactory interface
public:
    virtual ShapeObject *create_shape() override;
    virtual ShapeObject *create_shape(QPoint &begin, QPoint &end, QPen &pen, QBrush &brush) override;
};

#endif // SHAPELINE_H

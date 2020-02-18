#include "ShapeRectangle.h"
#include <QRect>

ShapeRectangle::ShapeRectangle()
    : ShapeObject ()
{
    
}

ShapeRectangle::ShapeRectangle(QPoint &begin, QPoint &end, QPen &pen, QBrush &brush)
    : ShapeObject (begin, end, pen, brush)
{
    
}

ShapeRectangle::~ShapeRectangle()
{
    
}


void ShapeRectangle::draw_shape(QPainter *painter)
{
    QRect rect(_begin_pos, _end_pos);
    painter->drawRect(rect);
}


ShapeObject *RectangleFactory::create_shape()
{
    return new ShapeRectangle();
}



ShapeObject *RectangleFactory::create_shape(QPoint &begin, QPoint &end, QPen &pen, QBrush &brush)
{
    return new ShapeRectangle(begin, end, pen, brush);
}


bool ShapeRectangle::is_selected(const QPoint &pos)
{
    QRect rect(_begin_pos, _end_pos);
    return rect.contains(pos);
}


void ShapeRectangle::draw_auxiliary(QPainter *painter)
{
    auto pre_pen = painter->pen();
    auto pre_brush = painter->brush();
    QPen pen(Qt::red, 3, Qt::DashDotLine);
    QBrush brush(Qt::NoBrush);
    painter->setPen(pen);
    painter->setBrush(brush);
    QRect rect(_begin_pos, _end_pos);
    painter->drawRect(rect);
    painter->setPen(pre_pen);
    painter->setBrush(pre_brush);
}


ShapeObject::TYPE ShapeRectangle::get_type() const
{
    return ShapeObject::SHAPE_RECTANGLE;
}

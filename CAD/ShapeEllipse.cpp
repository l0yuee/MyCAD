#include "ShapeEllipse.h"

#include <QRect>

ShapeEllipse::ShapeEllipse()
    : ShapeObject()
{
    
}

ShapeEllipse::ShapeEllipse(QPoint &begin, QPoint &end, QPen &pen, QBrush &brush)
    : ShapeObject (begin, end, pen, brush)
{
    
}

ShapeEllipse::~ShapeEllipse()
{
    
}


void ShapeEllipse::draw_shape(QPainter *painter)
{
    QRect rect(_begin_pos, _end_pos);
    painter->drawEllipse(rect);
}


ShapeObject *EllipseFactory::create_shape()
{
    return new ShapeEllipse();
}


ShapeObject *EllipseFactory::create_shape(QPoint &begin, QPoint &end, QPen &pen, QBrush &brush)
{
    return new ShapeEllipse(begin, end, pen, brush);
}


bool ShapeEllipse::is_selected(const QPoint &pos)
{
    QRect rect(_begin_pos, _end_pos);
    return rect.contains(pos);
}


void ShapeEllipse::draw_auxiliary(QPainter *painter)
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


ShapeObject::TYPE ShapeEllipse::get_type() const
{
    return ShapeObject::SHAPE_ELLIPSE;
}

#include "ShapeObject.h"

ShapeObject::ShapeObject()
{
    
}

ShapeObject::ShapeObject(QPoint &begin, QPoint &end, QPen &pen, QBrush &brush)
    : _begin_pos(begin), _end_pos(end), _pen(pen), _brush(brush)
{
    
}

ShapeObject::~ShapeObject()
{
    
}

QPair<QPoint, QPoint> ShapeObject::set_pos(QPoint &begin, QPoint &end)
{
    QPair<QPoint, QPoint> tmp;
    tmp.first = set_begin_pos(begin);
    tmp.second = set_end_pos(end);
    return tmp;
}

void ShapeObject::draw(QPainter *painter)
{
    // 保存之前的资源
    QPen pre_pen = painter->pen();
    QBrush pre_brush = painter->brush();
    
    // 设置自己的资源
    painter->setPen(_pen);
    painter->setBrush(_brush);
    
    // 画
    draw_shape(painter);
    
    // 还原资源
    painter->setPen(pre_pen);
    painter->setBrush(pre_brush);
}

void ShapeObject::save(QDataStream &ds)
{
    quint32 type_number = static_cast<quint32>(get_type());
    ds << type_number;
    ds << *this;
}

void ShapeObject::load(QDataStream &ds)
{
    ds >> *this;
}

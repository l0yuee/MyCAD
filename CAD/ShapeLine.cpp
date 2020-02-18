#include "ShapeLine.h"

ShapeLine::ShapeLine()
    : ShapeObject ()
{
    
}

ShapeLine::ShapeLine(QPoint &begin, QPoint &end, QPen &pen, QBrush &brush)
    : ShapeObject (begin, end, pen, brush)
{
    
}

ShapeLine::~ShapeLine()
{
    
}


void ShapeLine::draw_shape(QPainter *painter)
{
    painter->drawLine(_begin_pos, _end_pos);
}


ShapeObject *LineFactory::create_shape()
{
    return new ShapeLine();
}


ShapeObject *LineFactory::create_shape(QPoint &begin, QPoint &end, QPen &pen, QBrush &brush)
{
    return new ShapeLine(begin, end, pen, brush);
}


bool ShapeLine::is_selected(const QPoint &pos)
{
    int dx = 5, dy = 5;
    QVector<QPoint> vp;
    if(_begin_pos.x() < _end_pos.x()) {
        vp.push_back({_begin_pos.x() - dx, _begin_pos.y() + dy});
        vp.push_back({_begin_pos.x() + dx, _begin_pos.y() - dy});
        vp.push_back({_end_pos.x() + dx, _end_pos.y() - dy});
        vp.push_back({_end_pos.x() - dx, _end_pos.y() + dy});
        QPolygon gon(vp);
        return gon.containsPoint(pos, Qt::WindingFill);
    } else {
        vp.push_back({_begin_pos.x() - dx, _begin_pos.y() - dy});
        vp.push_back({_begin_pos.x() + dx, _begin_pos.y() + dy});
        vp.push_back({_end_pos.x() + dx, _end_pos.y() + dy});
        vp.push_back({_end_pos.x() - dx, _end_pos.y() - dy});
        QPolygon gon(vp);
        return gon.containsPoint(pos, Qt::WindingFill);
    }
}


void ShapeLine::draw_auxiliary(QPainter *painter)
{
    auto pre_pen = painter->pen();
    auto pre_brush = painter->brush();
    QPen pen(Qt::red, 3, Qt::DashDotLine);
    QBrush brush(Qt::NoBrush);
    painter->setPen(pen);
    painter->setBrush(brush);
    
    int dx = 5, dy = 5;
    QVector<QPoint> vp;
    if(_begin_pos.x() < _end_pos.x()) {
        vp.push_back({_begin_pos.x() - dx, _begin_pos.y() + dy});
        vp.push_back({_begin_pos.x() + dx, _begin_pos.y() - dy});
        vp.push_back({_end_pos.x() + dx, _end_pos.y() - dy});
        vp.push_back({_end_pos.x() - dx, _end_pos.y() + dy});
    } else {
        vp.push_back({_begin_pos.x() - dx, _begin_pos.y() - dy});
        vp.push_back({_begin_pos.x() + dx, _begin_pos.y() + dy});
        vp.push_back({_end_pos.x() + dx, _end_pos.y() + dy});
        vp.push_back({_end_pos.x() - dx, _end_pos.y() - dy});
    }
    QPolygon gon(vp);
    painter->drawPolygon(gon);
    
    painter->setPen(pre_pen);
    painter->setBrush(pre_brush);
}

ShapeObject::TYPE ShapeLine::get_type() const
{
    return ShapeObject::SHAPE_LINE;
}

#ifndef SHAPEOBJECT_H
#define SHAPEOBJECT_H

#include <QPoint>
#include <QPen>
#include <QBrush>
#include <QPair>
#include <QPainter>
#include <QDataStream>

class ShapeObject
{
public:
    ShapeObject();
    ShapeObject(QPoint &begin, QPoint &end, QPen &pen, QBrush &brush);
    virtual ~ShapeObject();
    
public:
    // 坐标
    inline QPoint set_begin_pos(QPoint &pos) { auto tmp = _begin_pos; _begin_pos = pos; return tmp; }
    inline QPoint set_end_pos(QPoint &pos) { auto tmp = _end_pos; _end_pos = pos; return tmp; }
    
    inline QPoint get_begin_pos() const { return _begin_pos; }
    inline QPoint get_end_pos() const { return _end_pos; }
    
    inline QPair<QPoint, QPoint> get_pos() { return {_begin_pos, _end_pos}; }
    QPair<QPoint, QPoint> set_pos(QPoint &begin, QPoint &end);
    
    // 画笔
    inline QPen get_pen() const { return _pen; }
    inline QPen set_pen(QPen &pen) { auto tmp = _pen; _pen = pen; return tmp; }
    
    // 画刷
    inline QBrush get_brush() const { return _brush; }
    inline QBrush set_brush(QBrush &brush) { auto tmp = _brush; _brush = brush; return tmp; }
    
    // 功能
    virtual void draw(QPainter *painter);
    virtual void draw_shape(QPainter *painter) = 0;
    virtual void draw_auxiliary(QPainter *painter) = 0;
    
    virtual bool is_selected(const QPoint &pos) = 0;
    
public:
    enum TYPE {
        SHAPE_LINE,
        SHAPE_RECTANGLE,
        SHAPE_ELLIPSE
    };
    virtual TYPE get_type() const = 0;
    virtual void save(QDataStream &ds);
    virtual void load(QDataStream &ds);
    friend QDataStream & operator <<(QDataStream &ds, ShapeObject &obj)
    {
        ds << obj.get_begin_pos() << obj.get_end_pos() << obj.get_pen() << obj.get_brush();
        return ds;
    }
    friend QDataStream & operator >>(QDataStream &ds, ShapeObject &obj)
    {
        ds >> obj._begin_pos;
        ds >> obj._end_pos;
        ds >> obj._pen;
        ds >> obj._brush;
        return ds;
    }

protected:
    QPoint _begin_pos;
    QPoint _end_pos;
    QPen _pen;
    QBrush _brush;
};

class ShapeFactory {
public:
    ShapeFactory() {}
    virtual ~ShapeFactory() {}
    virtual ShapeObject * create_shape() = 0;
    virtual ShapeObject * create_shape(QPoint &begin, QPoint &end, QPen &pen, QBrush &brush) = 0;
};

#endif // SHAPEOBJECT_H

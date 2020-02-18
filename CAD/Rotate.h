const int LINERANGE = 20;
const double PI = 3.14159265358979323846;
#include "math.h"
#include <QPoint>

inline void rotate(QPoint& beginPos,QPoint& endPos, double dblR)
{
    double x = (beginPos.x() + endPos.x())/2.0;
    double y = (beginPos.y() + endPos.y())/2.0;
    
    QPoint pos;
    
    pos.rx() = (long)((beginPos.x() - x)*cos(dblR) - (beginPos.y() - y)*sin(dblR) + x);
    pos.ry() = (long)((beginPos.x() - x)*sin(dblR) - (beginPos.y() - y)*cos(dblR) + y);
    
    
    beginPos = pos;
    
    pos.rx() = (long)((endPos.x() - x)*cos(dblR) - (endPos.y() - y)*sin(dblR) + x);
    pos.ry() = (long)((endPos.x() - x)*sin(dblR) - (endPos.y() - y)*cos(dblR) + y);
    
    endPos = pos;
}

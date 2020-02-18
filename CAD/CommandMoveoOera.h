#ifndef COMMANDMOVEOOERA_H
#define COMMANDMOVEOOERA_H

#include "CommandObject.h"
#include <QPoint>
#include "ShapeObject.h"

class CommandMoveOpera : public CommandObject
{
public:
    CommandMoveOpera();
    CommandMoveOpera(QPoint &p_b, QPoint &p_e, QPoint &c_b, QPoint &c_e, ShapeObject *shape);
    virtual ~CommandMoveOpera() override;
    
private:
    QPoint pre_begin;
    QPoint pre_end;
    QPoint new_begin;
    QPoint new_end;
    ShapeObject *current_shape;
    
    // CommandObject interface
public:
    virtual void undo() override;
    virtual void recover() override;
};

#endif // COMMANDMOVEOOERA_H

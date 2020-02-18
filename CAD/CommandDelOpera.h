#ifndef COMMANDDELOPERA_H
#define COMMANDDELOPERA_H

#include "CommandObject.h"


class CommandDelOpera : public CommandObject
{
public:
    CommandDelOpera();
    CommandDelOpera(QList<ShapeObject *> &list, ShapeObject *shape);
    virtual ~CommandDelOpera() override;
    
private:
    QList<ShapeObject *> *list_shape;
    ShapeObject *current_shape;
    
    // CommandObject interface
public:
    virtual void undo() override;
    virtual void recover() override;
};

#endif // COMMANDDELOPERA_H

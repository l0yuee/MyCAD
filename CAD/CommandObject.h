#ifndef COMMANDOBJECT_H
#define COMMANDOBJECT_H

#include <QList>
#include <ShapeObject.h>


class CommandObject
{
public:
    CommandObject();
    virtual ~CommandObject();
    
    virtual void undo() = 0;
    virtual void recover() = 0;
};

#endif // COMMANDOBJECT_H

#ifndef COMMANDADD_H
#define COMMANDADD_H

#include "CommandObject.h"

class CommandAddOpera : public CommandObject {
public:
    CommandAddOpera();
    CommandAddOpera(QList<ShapeObject *> &list, ShapeObject *shape);
    virtual ~CommandAddOpera() override;
    
private:
    QList<ShapeObject *> *list_shape;
    ShapeObject *current_shape;
    
    // CommandObject interface
public:
    virtual void undo() override;
    virtual void recover() override;
};

#endif // COMMANDADD_H

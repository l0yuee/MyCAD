#include "CommandDelOpera.h"

CommandDelOpera::CommandDelOpera()
{
    
}

CommandDelOpera::CommandDelOpera(QList<ShapeObject *> &list, ShapeObject *shape)
    : list_shape(&list), current_shape(shape)
{
    
}

CommandDelOpera::~CommandDelOpera()
{
    
}


void CommandDelOpera::undo()
{
    list_shape->push_back(current_shape);
}

void CommandDelOpera::recover()
{
    list_shape->pop_back();
}

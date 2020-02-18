#include "CommandAddOpera.h"

CommandAddOpera::CommandAddOpera()
{
    
}

CommandAddOpera::CommandAddOpera(QList<ShapeObject *> &list, ShapeObject *shape)
    : list_shape(&list), current_shape(shape)
{
    
}

CommandAddOpera::~CommandAddOpera()
{
    
}

void CommandAddOpera::undo()
{
    list_shape->pop_back();
}

void CommandAddOpera::recover()
{
    list_shape->push_back(current_shape);
}

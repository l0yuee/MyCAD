#include "CommandMoveoOera.h"

CommandMoveOpera::CommandMoveOpera()
{
    
}

CommandMoveOpera::CommandMoveOpera(QPoint &p_b, QPoint &p_e, QPoint &c_b, QPoint &c_e, ShapeObject *shape)
    : pre_begin(p_b), pre_end(p_e), new_begin(c_b), new_end(c_e), current_shape(shape)
{
    
}

CommandMoveOpera::~CommandMoveOpera()
{
    
}

void CommandMoveOpera::undo()
{
    current_shape->set_pos(pre_begin, pre_end);
}

void CommandMoveOpera::recover()
{
    current_shape->set_pos(new_begin, new_end);
}

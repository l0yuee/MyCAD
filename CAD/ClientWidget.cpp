#include "ClientWidget.h"
#include "ShapeLine.h"
#include "ShapeRectangle.h"
#include "ShapeEllipse.h"
#include <QMouseEvent>
#include "CommandAddOpera.h"
#include "CommandMoveoOera.h"
#include <QFileDialog>
#include <QSettings>

ClientWidget::ClientWidget(QWidget *parent) : QWidget(parent)
{
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, Qt::white);
    setPalette(pal);
    
    factory = new LineFactory();
    load_config();
}

ClientWidget::~ClientWidget()
{
    if(factory)
        delete factory;
    
    for(auto &item : vector_shape) {
        delete item;
    }
}

void ClientWidget::load_config()
{
    QFile file(ini_file);
    if(file.exists()) {
        file.close();
        // 存在读取
        QSettings ini(ini_file, QSettings::IniFormat);
        ini.beginGroup("pen");
        // 画笔
        QVariant qvariant;
        qvariant = ini.value("style");
        current_pen.setStyle((Qt::PenStyle)qvariant.toUInt());
        
        qvariant = ini.value("width");
        current_pen.setWidth(qvariant.toInt());
        
        qvariant = ini.value("color");
        current_pen.setColor(qvariant.value<QColor>());
        
        ini.endGroup();
        
        ini.beginGroup("brush");
        // 画刷
        qvariant = ini.value("style");
        current_brush.setStyle((Qt::BrushStyle)qvariant.toUInt());
        
        qvariant = ini.value("color");
        current_brush.setColor(qvariant.value<QColor>());
        
        ini.endGroup();
    } else {
        // 不存在则保存
        file.close();
        save_config();
    }
}

void ClientWidget::save_config()
{
    QSettings ini(ini_file, QSettings::IniFormat);
    ini.beginGroup("pen");
    // 画笔
    ini.setValue("style", QVariant((uint)current_pen.style()));
    ini.setValue("width", (int)current_pen.width());
    ini.setValue("color", current_pen.color());
    ini.endGroup();
    
    ini.beginGroup("brush");
    // 画刷
    ini.setValue("style", (uint)current_brush.style());
    ini.setValue("color", current_brush.color());
    ini.endGroup();
}

void ClientWidget::save_data()
{
    auto current_dir = QDir::currentPath();
    if(filename.isEmpty()) {
        filename = QFileDialog::getSaveFileName(this,
              tr("保存文件"), current_dir, tr("CAD Files (*.cad *.ad *.d);; All Files (*.*)"));
        if(filename.isEmpty()) {
            return ;
        }
    }
    // TODO: 
    QFile qf(filename);
    if(!qf.open(QIODevice::ReadWrite)) {
        return ;
    }
    QDataStream ds(&qf);
    
    for(auto &item : list_shape) {
        item->save(ds);
    }
    
    qf.close();
}

void ClientWidget::load_data()
{
    auto current_dir = QDir::currentPath();
    filename = QFileDialog::getOpenFileName(this,
          tr("打开文件"), current_dir, tr("CAD Files (*.cad *.d);; All Files (*.*)"));
    // TODO:
    if(filename.isEmpty()) {
        return ;
    }
    // 清空当前所有资源
    clear_resource();
    
    QFile qf(filename);
    if(!qf.open(QIODevice::ReadOnly)) {
        return ;
    }
    QDataStream ds(&qf);
    while (1) {
        quint32 type_number;
        ds >> type_number;
        if(ds.status() == QDataStream::ReadPastEnd) {
            break;
        }
        switch (static_cast<ShapeObject::TYPE>(type_number)) {
        case ShapeObject::TYPE::SHAPE_LINE:
            list_shape.push_back(new ShapeLine());
            break;
        case ShapeObject::TYPE::SHAPE_RECTANGLE:
            list_shape.push_back(new ShapeRectangle());
            break;
        case ShapeObject::TYPE::SHAPE_ELLIPSE:
            list_shape.push_back(new ShapeEllipse());
            break;
        }
        list_shape.back()->load(ds);
        current_shape = list_shape.back();
        emit on_tree_view_add_information();
        current_shape = nullptr;
        vector_shape.push_back(list_shape.back());
    }
    
    qf.close();
    repaint();
}

void ClientWidget::clear_resource()
{
    for(auto &item : vector_shape)
        delete item;
    vector_shape.clear();
    list_shape.clear();
    current_shape = nullptr;
    wait4undo.clear();
    wait4recover.clear();
}


void ClientWidget::mousePressEvent(QMouseEvent *event)
{
    emit update_statusbar(tr("绘制..."));
    current_mouse_pos = event->pos();
    if(event->button() == Qt::LeftButton) {
        if(selection_model) {
            // 选择模式
            is_moveing = true;
            current_shape = nullptr;
            for(auto iter = list_shape.rbegin(); iter != list_shape.rend(); ++iter) {
                if((*iter)->is_selected(event->pos())) {
                    current_shape = *iter;
                    current_shape_begin_pos = (*iter)->get_begin_pos();
                    current_shape_end_pos = (*iter)->get_end_pos();
                    break;
                }
            }
            emit on_tree_view_update_checked();
        } else {
            QPoint cur_begin = event->pos();
            current_shape = factory->create_shape(cur_begin, cur_begin, current_pen, current_brush);
            list_shape.push_back(current_shape);

            // 加入待撤销栈中
            wait4undo.push(new CommandAddOpera(list_shape, current_shape));
            // 清空恢复栈与图形池
            wait4recover.clear();
        }
    }
}

void ClientWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit update_statusbar(tr("就绪"));
    if(selection_model) {
        // 选择模式
        is_moveing = false;
        
        if(current_shape) {
            QPoint new_begin = current_shape->get_begin_pos(), new_end = current_shape->get_end_pos();
            if(!(current_shape_begin_pos ==  new_begin && current_shape_end_pos == new_end)) {
                // 加入待撤销栈中
                wait4undo.push(new CommandMoveOpera(current_shape_begin_pos, current_shape_end_pos, new_begin, new_end, current_shape));
            }
//            emit on_tree_view_update_checked();
        }
    } else {
        emit on_tree_view_add_information();
        current_shape = nullptr;
    }
    repaint();
}

void ClientWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(selection_model) {
        // 选择模式
        if(current_shape) {
            int dx = event->pos().x() - current_mouse_pos.x();
            int dy = event->pos().y() - current_mouse_pos.y();
            QPoint new_begin = current_shape->get_begin_pos() + QPoint(dx, dy);
            QPoint new_end = current_shape->get_end_pos() + QPoint(dx, dy);
            current_shape->set_begin_pos(new_begin);
            current_shape->set_end_pos(new_end);
            emit update_tree_view_item();
        }
    } else {
        if(current_shape) {
            QPoint pos = event->pos();
            current_shape->set_end_pos(pos);
        }
    }
    current_mouse_pos = event->pos();
    repaint();
}

void ClientWidget::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    painter->setPen(current_pen);
    painter->setBrush(current_brush);
    for(auto &item : list_shape) {
        item->draw(painter);
    }
    
    if(current_shape && selection_model) {
        current_shape->draw_auxiliary(painter);
    }
    
    delete painter;
}

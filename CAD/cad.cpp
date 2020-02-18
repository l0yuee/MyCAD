#include "cad.h"
#include "ui_cad.h"

#include <QMessageBox>
#include <QActionGroup>
#include <ShapeObject.h>
#include <ShapeLine.h>
#include <ShapeRectangle.h>
#include <ShapeEllipse.h>
#include "DrawSettingDialog.h"
#include "Rotate.h"
#include "CommandObject.h"
#include "CommandDelOpera.h"
#include <QFileDialog>
#include "aboutdialog.h"

CAD::CAD(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CAD)
{
    ui->setupUi(this);
    QActionGroup *action_group = new QActionGroup(this);
    action_group->addAction(ui->action_line);
    action_group->addAction(ui->action_rectangele);
    action_group->addAction(ui->action_ellipse);
    action_group->addAction(ui->action_select);
    
    model_of_tree_view = new QStandardItemModel(ui->treeView);
    QStringList s_l;
    s_l.push_back(tr("对象"));
    model_of_tree_view->setHorizontalHeaderLabels(s_l);
    ui->treeView->setModel(model_of_tree_view);
    
    set_statusbar(tr("就绪"));
    
    // 托盘
    trayicon = new QSystemTrayIcon(QIcon(":/img/res/shape.png"), this);
    trayicon->setContextMenu(ui->menu_5);
    trayicon->show();
    
    // 连接信号槽
    connect(ui->client_widget, &ClientWidget::update_statusbar, this, &CAD::set_statusbar);
}

CAD::~CAD()
{
    delete ui;
}

QStandardItem *CAD::get_tree_view_head_item(const QModelIndex &index)
{
    QStandardItem *current_item = model_of_tree_view->itemFromIndex(index);
    while (current_item->parent()) {
        current_item = current_item->parent();
    }
    return current_item;
}

ShapeObject *CAD::get_tree_view_data(const QModelIndex &index)
{
    QStandardItem *current_item = get_tree_view_head_item(index);
    return (ShapeObject *)(current_item->data().toLongLong());
}

void CAD::tree_view_update()
{
//    model_of_tree_view->destroyed();
//    model_of_tree_view = new QStandardItemModel(ui->treeView);
    model_of_tree_view->clear();
    for(auto &item : ui->client_widget->list_shape) {
        QStandardItem *standard_item_shape = nullptr;
        QStandardItem *standard_item_pen = new QStandardItem(tr("Pen"));
        QStandardItem *standard_item_brush = new QStandardItem(tr("Brush"));
        QStandardItem *standard_item_pos = new QStandardItem(tr("Postition"));
        
        auto shape = item;
        auto pen = shape->get_pen();
        auto brush = shape->get_brush();
        // 添加图形信息
        switch(shape->get_type()) {
        case ShapeObject::SHAPE_LINE:
            standard_item_shape = new QStandardItem(tr("Line"));
            break;
        case ShapeObject::SHAPE_RECTANGLE:
            standard_item_shape = new QStandardItem(tr("Rectangle"));
            break;
        case ShapeObject::SHAPE_ELLIPSE:
            standard_item_shape = new QStandardItem(tr("Ellipse"));
            break;
        }
        standard_item_shape->setChild(0, standard_item_pos);
        standard_item_shape->setChild(1, standard_item_pen);
        standard_item_shape->setChild(2, standard_item_brush);
        // 添加位置信息
        standard_item_pos->setChild(0, new QStandardItem(QString(tr("Begin: (%1, %2)")).
                                                               arg(shape->get_begin_pos().x()).arg(shape->get_begin_pos().y())));
        standard_item_pos->setChild(1, new QStandardItem(QString(tr("End: (%1, %2)")).
                                                               arg(shape->get_end_pos().x()).arg(shape->get_end_pos().y())));
        // 添加画笔信息
        standard_item_pen->setChild(0, new QStandardItem(QString(tr("Width: %1")).arg(pen.width())));
        standard_item_pen->setChild(1, new QStandardItem(QString(tr("Style: %1")).arg(pen.style())));
        standard_item_pen->setChild(2, new QStandardItem(QString(tr("RGB: (%1, %2, %3)")).
                                                         arg(pen.color().red()).arg(pen.color().green()).arg(pen.color().blue())));
        
        // 添加画刷信息
        standard_item_brush->setChild(0, new QStandardItem(QString(tr("Style: %1")).arg(brush.style())));
        standard_item_brush->setChild(1, new QStandardItem(QString(tr("RGB: (%1, %2, %3)")).
                                                           arg(brush.color().red()).arg(brush.color().green()).arg(brush.color().blue())));
        
        standard_item_shape->setData((qlonglong)shape);
        //    ShapeObject *obj = (ShapeObject *)(standard_item_shape->data().toLongLong());
        model_of_tree_view->appendRow(standard_item_shape);
    }
}

void CAD::set_statusbar(QString info)
{
    ui->statusBar->showMessage(info);
}

void CAD::update_tree_view_item()
{
    auto iter = ui->client_widget->list_shape.begin();
    while (iter != ui->client_widget->list_shape.end()) {
        if(*iter == ui->client_widget->current_shape) {
            break;
        }
        ++iter;
    }
    int index = iter - ui->client_widget->list_shape.begin();
    auto current_item = model_of_tree_view->item(index);
    auto current_item_pos = current_item->child(0);
    // 修改坐标
    current_item_pos->child(0)->setText(QString(tr("Begin: (%1, %2)")).
                                        arg((*iter)->get_begin_pos().x()).arg((*iter)->get_begin_pos().y()));
    current_item_pos->child(1)->setText(QString(tr("End: (%1, %2)")).
                                        arg((*iter)->get_end_pos().x()).arg((*iter)->get_end_pos().y()));
    
    auto current_item_pen = current_item->child(1), current_item_brush = current_item->child(2);
    // 修改画笔
    auto pen = ui->client_widget->current_shape->get_pen();
    current_item_pen->child(0)->setText(QString(tr("Width: %1")).arg(pen.width()));
    current_item_pen->child(1)->setText(QString(tr("Style: %1")).arg(pen.style()));
    current_item_pen->child(2)->setText(QString(tr("RGB: (%1, %2, %3)")).
                                        arg(pen.color().red()).arg(pen.color().green()).arg(pen.color().blue()));
    
    // 修改画刷
    auto brush = ui->client_widget->current_shape->get_brush();
    current_item_brush->child(0)->setText(QString(tr("Style: %1")).arg(pen.style()));
    current_item_brush->child(1)->setText(QString(tr("RGB: (%1, %2, %3)")).
                                        arg(pen.color().red()).arg(pen.color().green()).arg(pen.color().blue()));
}

void CAD::on_tree_view_add_information()
{
    QStandardItem *standard_item_shape = nullptr;
    QStandardItem *standard_item_pen = new QStandardItem(tr("Pen"));
    QStandardItem *standard_item_brush = new QStandardItem(tr("Brush"));
    QStandardItem *standard_item_pos = new QStandardItem(tr("Postition"));
    auto shape = ui->client_widget->list_shape.back();
    auto pen = shape->get_pen();
    auto brush = shape->get_brush();
    
    // 添加图形信息
    switch(shape->get_type()) {
    case ShapeObject::SHAPE_LINE:
        standard_item_shape = new QStandardItem(tr("Line"));
        break;
    case ShapeObject::SHAPE_RECTANGLE:
        standard_item_shape = new QStandardItem(tr("Rectangle"));
        break;
    case ShapeObject::SHAPE_ELLIPSE:
        standard_item_shape = new QStandardItem(tr("Ellipse"));
        break;
    }
    standard_item_shape->setChild(0, standard_item_pos);
    standard_item_shape->setChild(1, standard_item_pen);
    standard_item_shape->setChild(2, standard_item_brush);
    // 添加位置信息
    standard_item_pos->setChild(0, new QStandardItem(QString(tr("Begin: (%1, %2)")).
                                                           arg(shape->get_begin_pos().x()).arg(shape->get_begin_pos().y())));
    standard_item_pos->setChild(1, new QStandardItem(QString(tr("End: (%1, %2)")).
                                                           arg(shape->get_end_pos().x()).arg(shape->get_end_pos().y())));
    // 添加画笔信息
    standard_item_pen->setChild(0, new QStandardItem(QString(tr("Width: %1")).arg(pen.width())));
    standard_item_pen->setChild(1, new QStandardItem(QString(tr("Style: %1")).arg(pen.style())));
    standard_item_pen->setChild(2, new QStandardItem(QString(tr("RGB: (%1, %2, %3)")).
                                                     arg(pen.color().red()).arg(pen.color().green()).arg(pen.color().blue())));
    
    // 添加画刷信息
    standard_item_brush->setChild(0, new QStandardItem(QString(tr("Style: %1")).arg(brush.style())));
    standard_item_brush->setChild(1, new QStandardItem(QString(tr("RGB: (%1, %2, %3)")).
                                                       arg(brush.color().red()).arg(brush.color().green()).arg(brush.color().blue())));
    
    standard_item_shape->setData((qlonglong)shape);
    //    ShapeObject *obj = (ShapeObject *)(standard_item_shape->data().toLongLong());
    model_of_tree_view->appendRow(standard_item_shape);
}

void CAD::on_tree_view_del_information()
{
    auto iter = ui->client_widget->list_shape.begin();
    while (iter != ui->client_widget->list_shape.end()) {
        if(*iter == ui->client_widget->current_shape) {
            break;
        }
        ++iter;
    }
    int index = iter - ui->client_widget->list_shape.begin();
//    auto current_item = model_of_tree_view->item(index);
    model_of_tree_view->removeRow(index);
}

void CAD::on_tree_view_update_checked()
{
    if(!ui->client_widget->current_shape) {
        ui->treeView->clearSelection();
        return ;
    }
    auto iter = ui->client_widget->list_shape.begin();
    while (iter != ui->client_widget->list_shape.end()) {
        if(*iter == ui->client_widget->current_shape) {
            break;
        }
        ++iter;
    }
    int index = iter - ui->client_widget->list_shape.begin();
    auto current_item = model_of_tree_view->item(index);
    ui->treeView->setCurrentIndex(current_item->index());
}

void CAD::on_action1_aboutQT_triggered()
{
    QMessageBox().aboutQt(this, tr("About Qt"));
}

void CAD::on_action_line_triggered()
{
    if(ui->client_widget->factory)
        delete ui->client_widget->factory;
    ui->client_widget->factory = new LineFactory();
    
    ui->action_select->setChecked(false);
    ui->client_widget->selection_model = false;
    ui->client_widget->current_shape = nullptr;
}

void CAD::on_action_rectangele_triggered()
{
    if(ui->client_widget->factory)
        delete ui->client_widget->factory;
    ui->client_widget->factory = new RectangleFactory();
    
    ui->action_select->setChecked(false);
    ui->client_widget->selection_model = false;
    ui->client_widget->current_shape = nullptr;
}

void CAD::on_action_ellipse_triggered()
{
    if(ui->client_widget->factory)
        delete ui->client_widget->factory;
    ui->client_widget->factory = new EllipseFactory();
    
    ui->action_select->setChecked(false);
    ui->client_widget->selection_model = false;
    ui->client_widget->current_shape = nullptr;
}

void CAD::on_action_draw_setting_triggered()
{
    auto pen = ui->client_widget->current_pen;
    auto brush = ui->client_widget->current_brush;
    draw_setting_dialog = new DrawSettingDialog(pen, brush, this);
    
    if(draw_setting_dialog->exec() == DrawSettingDialog::Accepted) {
        if(ui->client_widget->selection_model && ui->client_widget->current_shape) {
            ui->client_widget->current_shape->set_pen(draw_setting_dialog->_pen);
            ui->client_widget->current_shape->set_brush(draw_setting_dialog->_brush);
            // 更新tree视图
            update_tree_view_item();
        } else {
            ui->client_widget->current_pen = draw_setting_dialog->_pen;
            ui->client_widget->current_brush = draw_setting_dialog->_brush;
        }
    }
    delete draw_setting_dialog;
}

void CAD::on_action_select_triggered(bool checked)
{
    ui->client_widget->selection_model = checked;
}

void CAD::on_action_delete_triggered()
{
    if(ui->client_widget->selection_model && ui->client_widget->current_shape) {
        on_tree_view_del_information();
        
        ui->client_widget->list_shape.removeOne(ui->client_widget->current_shape);
        auto &wait4undo = ui->client_widget->wait4undo;
        //        auto &wait4recover = ui->client_widget->wait4recover;
        wait4undo.push(new CommandDelOpera(ui->client_widget->list_shape, ui->client_widget->current_shape));
        // 暂时不释放资源
        ui->client_widget->current_shape = nullptr;
    }
    ui->client_widget->repaint();
}

void CAD::on_action_rotation_triggered()
{
    if(ui->client_widget->selection_model && ui->client_widget->current_shape) {
        QPoint begin = ui->client_widget->current_shape->get_begin_pos();
        QPoint end = ui->client_widget->current_shape->get_end_pos();
        rotate(begin, end, PI / 2);
        ui->client_widget->current_shape->set_begin_pos(begin);
        ui->client_widget->current_shape->set_end_pos(end);
    }
    ui->client_widget->repaint();
}

void CAD::on_action_undo_triggered()
{
    auto &wait4undo = ui->client_widget->wait4undo;
    auto &wait4recover = ui->client_widget->wait4recover;
    if(!wait4undo.empty()) {
        auto item = wait4undo.top();
        wait4undo.pop();
        item->undo();
        // 加入待恢复栈中
        wait4recover.push(item);
    }
    ui->action_select->setChecked(false);
    ui->client_widget->selection_model = false;
    ui->action_line->setChecked(true);
    ui->client_widget->repaint();
    tree_view_update();
}

void CAD::on_action_recover_triggered()
{
    auto &wait4undo = ui->client_widget->wait4undo;
    auto &wait4recover = ui->client_widget->wait4recover;
    if(!wait4recover.empty()) {
        auto item = wait4recover.top();
        wait4recover.pop();
        item->recover();
        // 加入待撤销栈中
        wait4undo.push(item);
    }
    ui->action_select->setChecked(false);
    ui->client_widget->selection_model = false;
    ui->action_line->setChecked(true);
    ui->client_widget->repaint();
    tree_view_update();
}

void CAD::on_action_quit_triggered()
{
    close();
}

void CAD::on_action_file_open_triggered()
{
    ui->client_widget->load_data();
}

void CAD::on_action_file_save_triggered()
{
    ui->client_widget->save_data();
}

void CAD::on_treeView_clicked(const QModelIndex &index)
{
    ui->client_widget->current_shape = get_tree_view_data(index);
    ui->action_select->setChecked(true);
    ui->client_widget->selection_model = true;
    ui->client_widget->repaint();
}

void CAD::on_treeView_doubleClicked(const QModelIndex &index)
{
    ui->client_widget->current_shape = get_tree_view_data(index);
    on_action_draw_setting_triggered();
}

void CAD::on_action_aboutme_triggered()
{
    AboutDialog dlg;
    dlg.exec();
}


void CAD::closeEvent(QCloseEvent *event)
{
    ui->client_widget->save_config();
}

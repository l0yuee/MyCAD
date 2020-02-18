#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <ShapeObject.h>
#include <QStack>
#include "CommandObject.h"

class ClientWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget() override;
    
signals:
    void on_tree_view_add_information();
    void on_tree_view_update_checked();
    void update_tree_view_item();
    void update_statusbar(QString info);
    
public slots:
    
public:
    ShapeFactory *factory;  // 工厂类
    ShapeObject *current_shape = nullptr;   // 当前图形
    QList<ShapeObject *> list_shape;        // 图形链表
    QVector<ShapeObject *> vector_shape;    // 图形池，释放用
    
    QPen current_pen;       // 当前画笔
    QBrush current_brush;   // 当前画刷
    
    bool selection_model = false;   // 选择模式
    bool is_moveing = false;    //是否正在移动
    
    QPoint current_mouse_pos;   // 当前鼠标位置
    QPoint current_shape_begin_pos; // 当前图形开始坐标
    QPoint current_shape_end_pos;   // 当前图形结束坐标
    
    QString filename;   // 当前文件
    
    QStack<CommandObject *> wait4undo;
    QStack<CommandObject *> wait4recover;
    
public:
    void save_data();
    void load_data();
    void clear_resource();
    
    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // CLIENTWIDGET_H

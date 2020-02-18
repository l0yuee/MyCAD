#ifndef CAD_H
#define CAD_H

#include <QMainWindow>
#include "DrawSettingDialog.h"
#include <QStandardItemModel>
#include "ShapeObject.h"
#include "ClientWidget.h"
#include <QSystemTrayIcon>


namespace Ui {
class CAD;
}

class CAD : public QMainWindow
{
    Q_OBJECT

public:
    explicit CAD(QWidget *parent = nullptr);
    ~CAD();
    
public:
    QStandardItem *get_tree_view_head_item(const QModelIndex &index);
    ShapeObject *get_tree_view_data(const QModelIndex &index);
    
    void tree_view_update();
    
public slots:
    void on_tree_view_add_information();
    void on_tree_view_del_information();    
    void on_tree_view_update_checked();
    void update_tree_view_item();
    void set_statusbar(QString info);

private slots:
    void on_action1_aboutQT_triggered();
    
    void on_action_line_triggered();
    
    void on_action_rectangele_triggered();
    
    void on_action_ellipse_triggered();
    
    void on_action_draw_setting_triggered();
    
    void on_action_select_triggered(bool checked);
    
    void on_action_delete_triggered();
    
    void on_action_rotation_triggered();
    
    void on_action_undo_triggered();
    
    void on_action_recover_triggered();
    
    void on_action_quit_triggered();
    
    void on_action_file_open_triggered();
    
    void on_action_file_save_triggered();
    
    void on_treeView_clicked(const QModelIndex &index);
    
    void on_treeView_doubleClicked(const QModelIndex &index);
    
    void on_action_aboutme_triggered();
    
private:
    Ui::CAD *ui;
    QSystemTrayIcon *trayicon;
    DrawSettingDialog *draw_setting_dialog;
    QStandardItemModel *model_of_tree_view;
    
    // QWidget interface
protected:
    virtual void closeEvent(QCloseEvent *event) override;
};

#endif // CAD_H

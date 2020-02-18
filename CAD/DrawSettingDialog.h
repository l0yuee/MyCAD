#ifndef DRAWSETTINGDIALOG_H
#define DRAWSETTINGDIALOG_H

#include <QDialog>
#include <QPen>
#include <QBrush>
#include <QMap>

namespace Ui {
class DrawSettingDialog;
}

class DrawSettingDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DrawSettingDialog(QWidget *parent = nullptr);
    DrawSettingDialog(QPen &pen, QBrush &brush, QWidget *parent = nullptr);
    ~DrawSettingDialog();
    
    void init_maphash();
    
public slots:
    void pen_style_changed(int);
    void brush_style_changed(int);
    void pen_width_changed(int);
    
private:
    Ui::DrawSettingDialog *ui;
    
public:
    QPen _pen;
    QBrush _brush;
    QMap<int, Qt::PenStyle> map_pen_style;
    QMap<int, Qt::BrushStyle> map_brush_style;
private slots:
    void on_pushButton_pen_color_clicked();
    void on_pushButton_brush_color_clicked();
};

#endif // DRAWSETTINGDIALOG_H

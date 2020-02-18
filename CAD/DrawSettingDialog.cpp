#include "DrawSettingDialog.h"
#include "ui_drawsettingdialog.h"

#include <QColorDialog>

DrawSettingDialog::DrawSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrawSettingDialog)
{
    ui->setupUi(this);
    
    init_maphash();
}

DrawSettingDialog::DrawSettingDialog(QPen &pen, QBrush &brush, QWidget *parent) : 
    QDialog(parent),
    ui(new Ui::DrawSettingDialog), 
    _pen(pen),
    _brush(brush)
{
    ui->setupUi(this);
    
    init_maphash();
    // 设置画笔属性
    // 风格
    auto pen_style = _pen.style();
    for(int i = 0; i < map_pen_style.size(); i++) {
        if(map_pen_style[i] == pen_style) {
            ui->comboBox_pen_style->setCurrentIndex(i);
        }
    }
    // 宽度
    auto pen_width = _pen.width();
    ui->spinBox_pen_width->setValue(pen_width);
    
    // 设置画刷属性
    // 风格
    auto brush_style = _brush.style();
    for(int i = 0; i < map_brush_style.size(); i++) {
        if(map_brush_style[i] == brush_style) {
            ui->comboBox_brush_style->setCurrentIndex(i);
        }
    }
}

DrawSettingDialog::~DrawSettingDialog()
{
    delete ui;
}

void DrawSettingDialog::init_maphash()
{
    int index = 0;
    map_pen_style[index++] = Qt::NoPen;
    map_pen_style[index++] = Qt::SolidLine;
    map_pen_style[index++] = Qt::DashLine;
    map_pen_style[index++] = Qt::DotLine;
    map_pen_style[index++] = Qt::DashDotLine;
    map_pen_style[index++] = Qt::DashDotDotLine;
    map_pen_style[index++] = Qt::CustomDashLine;
    
    index = 0;
    map_brush_style[index++] = Qt::NoBrush;
    map_brush_style[index++] = Qt::SolidPattern;
    map_brush_style[index++] = Qt::Dense1Pattern;
    map_brush_style[index++] = Qt::Dense2Pattern;
    map_brush_style[index++] = Qt::Dense3Pattern;
    map_brush_style[index++] = Qt::Dense4Pattern;
    map_brush_style[index++] = Qt::Dense5Pattern;
    map_brush_style[index++] = Qt::Dense6Pattern;
    map_brush_style[index++] = Qt::Dense7Pattern;
    map_brush_style[index++] = Qt::HorPattern;
    map_brush_style[index++] = Qt::VerPattern;
    map_brush_style[index++] = Qt::CrossPattern;
    map_brush_style[index++] = Qt::BDiagPattern;
    map_brush_style[index++] = Qt::FDiagPattern;
    map_brush_style[index++] = Qt::DiagCrossPattern;
    map_brush_style[index++] = Qt::LinearGradientPattern;
    map_brush_style[index++] = Qt::ConicalGradientPattern;
    map_brush_style[index++] = Qt::RadialGradientPattern;
    map_brush_style[index++] = Qt::TexturePattern;
}

void DrawSettingDialog::pen_style_changed(int index)
{
    _pen.setStyle(map_pen_style[index]);
}

void DrawSettingDialog::brush_style_changed(int index)
{
    _brush.setStyle(map_brush_style[index]);
}

void DrawSettingDialog::pen_width_changed(int width)
{
    _pen.setWidth(width);
}

void DrawSettingDialog::on_pushButton_pen_color_clicked()
{
    QColor color = QColorDialog::getColor(_pen.color(), this);
    _pen.setColor(color);
    
    QString s = "color: rgb(";
    s += QString::number(color.red()) + ", " + QString::number(color.green()) + ", " + QString::number(color.blue()) + ")";   
    ui->pushButton_pen_color->setStyleSheet(s);
}

void DrawSettingDialog::on_pushButton_brush_color_clicked()
{
    QColor color = QColorDialog::getColor(_brush.color(), this);
    _brush.setColor(color);
    
    QString s = "background: rgb(";
    s += QString::number(color.red()) + ", " + QString::number(color.green()) + ", " + QString::number(color.blue()) + ")";
    ui->pushButton_brush_color->setStyleSheet(s);
}

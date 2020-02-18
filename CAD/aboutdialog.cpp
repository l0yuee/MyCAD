#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    
    img = new QImage();
    img->load(":/img/res/shape.png");
    ui->label_img->setPixmap(QPixmap::fromImage(*img));
}

AboutDialog::~AboutDialog()
{
    delete ui;
    delete img;
}

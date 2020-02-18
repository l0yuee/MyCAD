#include "cad.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CAD w;
    w.show();

    return a.exec();
}

#include "mainwindow.h"

#include <QApplication>
#include "Formula.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Formula formula("Na23F5(OH)2");
    formula.parse();
    w.show();
    return a.exec();
}

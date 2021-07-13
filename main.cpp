#include "mainwindow.h"

#include <QApplication>
#include "formula.h"
#include "constants.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Formula formula("Na23H15(OH)2");
    formula.parse();
    formula.getTreeView()->printLeaves();
    w.show();
    std::cout << "\nMolecular mass: " << formula.getMolecularMass();
    std::cout << "\nPercentage of H: " << formula.getMolecularMassPercentageOfAtom(AtomsInfo.find("H")->second);
    return a.exec();
}

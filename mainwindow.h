#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "formula.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_textEdit_textChanged();

public slots:
    void onParseResult(int resultCode, std::string text);

signals:
    void formulaTextChganged(std::string value);

private:
    Ui::MainWindow *ui;
    Formula* formula;

};
#endif // MAINWINDOW_H

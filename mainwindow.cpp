#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->formula = new Formula("");
    QObject::connect(this, &MainWindow::formulaTextChganged, formula, &Formula::setFormulaText);
    QObject::connect(formula, &Formula::parseResult, this, &MainWindow::onParseResult);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_textEdit_textChanged()
{
    qDebug() << this->ui->textEdit->toPlainText();
    emit formulaTextChganged(this->ui->textEdit->toPlainText().toStdString());
}

void MainWindow::onParseResult(int resultCode, std::string text)
{
    switch (resultCode) {
    case 1: {
        this->ui->resultValue->setText(QString::fromStdString(std::to_string(this->formula->getMolecularMass())));
    } break;
    case -3: {
        this->ui->resultValue->setText(QString::fromStdString(text));
    }
    }
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->kostenLineEdit, SIGNAL(textChanged(QString)), this, SLOT(calculateForgePoints()));
    connect(ui->faktorDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(calculateForgePoints()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculateForgePoints(){
    int kosten = ui->kostenLineEdit->text().toInt();
    double faktor = ui->faktorDoubleSpinBox->value();
    ui->resultLineEdit->setText(QString().number(qRound(kosten * faktor)));
}

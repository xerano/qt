#include "sensorchart.h"
#include "ui_sensorchart.h"

SensorChart::SensorChart(QWidget *parent) : 
    QMainWindow(parent), 
    ui(new Ui::SensorChart)
{
	ui->setupUi(this);
    connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(onDateChanged()));
}

SensorChart::~SensorChart(){
    delete ui;
}

void SensorChart::onResult(QNetworkReply *reply){

}

void SensorChart::onDateChanged(){
    m_selectedDate = ui->calendarWidget->selectedDate();
    qDebug() << m_selectedDate << endl;
}

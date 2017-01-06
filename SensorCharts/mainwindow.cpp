#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->updateButton, SIGNAL(clicked()), this, SLOT(onUpdateButtonPressed()));
    connect(ui->comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(onSelectedSensorChanged()));
    connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(onDateChanged()));
    m_networkAccessManager = new QNetworkAccessManager();
    connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onDataReceived(QNetworkReply*)));
    m_currentDate = QDate::currentDate();

    m_chartView = new QChartView();
    m_chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(m_chartView);
    getSensors();

    ui->lcdCurrentTemp->setPalette(Qt::red);
    ui->lcdCurrentVCC->setPalette(Qt::red);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_networkAccessManager;
}

void MainWindow::onDateChanged(){
    m_currentDate = ui->calendarWidget->selectedDate();
    qDebug() << m_currentDate << endl;
    getSensorData();
}

void MainWindow::onDataReceived(QNetworkReply *reply){
    if(reply->url().query().length()>0 && reply->url().query().contains("from")){
         QString data = (QString) reply->readAll();

         QJsonDocument d = QJsonDocument::fromJson(data.toUtf8());

         QJsonArray a = d.array();

         QLineSeries *series = new QLineSeries();

         for (int i = 0; i < a.size(); i++){
             QJsonValue val = a.at(i);

             double temp = val.toObject().value("value").toString().toDouble();

             QDateTime timestamp = QDateTime::fromString(val.toObject().value("sensor_ts").toString(), "yyyy-MM-dd hh:mm:ss");

             series->append(timestamp.toMSecsSinceEpoch(), temp);
         }

         QChart *chart = new QChart();
         chart->addSeries(series);
         chart->legend()->hide();
         chart->setTitle("Temperatur");

         QDateTimeAxis *axisX = new QDateTimeAxis;
         axisX->setTickCount(10);
         axisX->setFormat("hh:mm");
         axisX->setTitleText("Zeit");
         chart->addAxis(axisX, Qt::AlignBottom);
         series->attachAxis(axisX);

         QValueAxis *axisY = new QValueAxis;
         axisY->setLabelFormat("%.2f");
         axisY->setTitleText("Temp");
         axisY->setRange(-30, 40);
         axisY->setTickCount(8);

         axisY->setGridLineVisible();

         QPen axisPen(QRgb(0x000000));
         axisPen.setWidth(1);
         axisY->setGridLinePen(axisPen);

         chart->addAxis(axisY, Qt::AlignLeft);
         series->attachAxis(axisY);

        m_chartView->setChart(chart);
    } else if (reply->url().query().length()>0){
        QString data = (QString) reply->readAll();
        QJsonDocument d = QJsonDocument::fromJson(data.toUtf8());
        QJsonObject o = d.object();
        double temp = o.value("value").toString().toDouble();
        double vcc = o.value("vcc").toString().toDouble();
        ui->lcdCurrentTemp->display(temp);
        ui->lcdCurrentVCC->display(vcc);
        getSensorData();
    } else {
        QString data = (QString) reply->readAll();
        QJsonDocument d = QJsonDocument::fromJson(data.toUtf8());
        QJsonArray a = d.array();
        for(int i = 0; i < a.size(); i++){
            QJsonValue val = a.at(i);
            ui->comboBox->addItem(val.toObject().value("sensor_id").toString());
        }
        getSensorData();
    }
}

void MainWindow::getSensors(){
    QUrl url("http://192.168.178.70/~alarm/sensors.php");
    QNetworkRequest request;
    request.setUrl(url);

    m_networkAccessManager->get(request);
}

void MainWindow::getSensorData(){
    QString currentDateString = m_currentDate.toString("yyyy-MM-dd");
    QUrl url;
    url.setUrl("http://192.168.178.70/~alarm/sensors.php");
    url.setQuery("sensor_id="+ui->comboBox->currentText()+"&from="+currentDateString + " 00:00:00&to=" + currentDateString +" 23:59:59");
    qDebug() << url << endl;

    QNetworkRequest request;
    request.setUrl(url);

    m_networkAccessManager->get(request);
}

void MainWindow::onUpdateButtonPressed(){
    m_currentDate = ui->calendarWidget->selectedDate();
    updateSensor();
}


void MainWindow::updateSensor()
{
    QUrl url;
    url.setUrl("http://192.168.178.70/~alarm/sensors.php");
    url.setQuery("sensor_id="+ui->comboBox->currentText());
    qDebug() << url << endl;

    QNetworkRequest request;
    request.setUrl(url);

    m_networkAccessManager->get(request);
}

void MainWindow::onSelectedSensorChanged(){
    updateSensor();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(onDateChanged()));
    m_networkAccessManager = new QNetworkAccessManager();
    connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onDataReceived(QNetworkReply*)));
    m_currentDate = QDate::currentDate();

    m_chartView = new QChartView();
    m_chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(m_chartView);

    getSensorData();
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
     QString data = (QString) reply->readAll();
     qDebug() << data << endl;

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
     axisY->setRange(-40, 40);
     axisY->setTickCount(9);

     axisY->setGridLineVisible();

     QPen axisPen(QRgb(0x000000));
     axisPen.setWidth(1);
     axisY->setGridLinePen(axisPen);

     chart->addAxis(axisY, Qt::AlignLeft);
     series->attachAxis(axisY);

    m_chartView->setChart(chart);
}

void MainWindow::getSensorData(){
    QUrl url("http://192.168.178.70/~alarm/sensors.php?sensor_id=sensors/temp/1&from="+m_currentDate.toString("yyyy-MM-dd"));
    qDebug() << url << endl;

    QNetworkRequest request;
    request.setUrl(url);

    m_networkAccessManager->get(request);
}



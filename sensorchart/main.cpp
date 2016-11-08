#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDate>
#include <QDebug>
#include "sensorchart.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[]){

	QApplication a(argc, argv);

	SensorChart c;
	c.show();

/*
	QLineSeries *series = new QLineSeries();

	QString sensor = "sensors/temp/1";
	QDate today = QDate::currentDate();

	QNetworkAccessManager nam;
	QUrl url("http://192.168.178.70/alarm/sensors.php?sensor_id="+sensor+"&from="+today.toString("yyyy-MM-dd"));
	QNetworkRequest request;
	request.setUrl(url);
	QNetworkReply *reply = nam.get(request);

	qDebug() << url << endl;
*/
/**
	series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
*/

    return a.exec();

}

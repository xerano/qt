#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QDateTime>
#include <QDebug>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QLineSeries>
#include <QChartView>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QCategoryAxis>


QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QDate m_currentDate;
    QChartView *m_chartView;
    QNetworkAccessManager *m_networkAccessManager;
    void getSensorData();
    void getSensors();

private slots:
    void onDateChanged();
    void onDataReceived(QNetworkReply*);
    void onUpdateButtonPressed();
    void onSelectedSensorChanged();
};

#endif // MAINWINDOW_H

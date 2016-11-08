#include <QMainWindow>
#include <QNetworkReply>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDate>
#include <QDebug>

namespace Ui {
    class SensorChart;
}

class SensorChart : public QMainWindow {
    Q_OBJECT

    public:
        explicit SensorChart(QWidget *parent=0);
        ~SensorChart();

    private slots:
        void onResult(QNetworkReply* reply);
        void onDateChanged();

    private:
        Ui::SensorChart *ui;
        QDate m_selectedDate;
};

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QLineSeries *series = new QLineSeries();

    int ran;
    srand (time(NULL));
    series->append(0,0);
    for(int i=1;i<11;i++){
        ran = rand() % 10 + 1;
        series->append(i,ran);
    }
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Ejemplo de histograma en QT creator");
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
#ifndef LEFTDOWNWIDGET_H
#define LEFTDOWNWIDGET_H

#include <QWidget>
#include <QtCharts>

#include "qwchartview.h"

using namespace QtCharts;

class MainWindow;

class leftDownWidget : public QWChartView {
    Q_OBJECT
   public:
    explicit leftDownWidget(QWidget *parent = nullptr);
    void paintStaticChart();
    void updateStaticChart();
   signals:

   public slots:

private:
    QLineSeries * series0;
    bool isexist0;
    QLineSeries * series1;
    bool isexist1;
    QLineSeries * series2;
    bool isexist2;
    QLineSeries * series3;
    bool isexist3;
    QValueAxis *axisX;
    QValueAxis *axisY;

    MainWindow *pa;

private slots:
    void on_LegendMarkerClicked(); //图例单击槽函数,自定义槽函数
    void on_mouseMovePoint(QPoint point); //鼠标移动事件，自定义槽函数
};

#endif  // LEFTDOWNWIDGET_H

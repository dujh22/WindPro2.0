#include "leftdownwidget.h"
#include "global.h"
#include "mainwindow.h"
#include  "qwchartview.h"
#include <QDebug>

leftDownWidget::leftDownWidget(QWidget *parent) : QWChartView(parent) {
    // setMinimumSize(400,200);
    isexist0 = false;
    isexist1 = false;
    isexist2 = false;
    isexist3 = false;

    pa = (MainWindow *)parent;
}

void leftDownWidget::paintStaticChart() {
    //创建图表
    QChart * chart = new QChart();
    chart->setTitle(tr("数据源2源数据图像"));
    this->setChart(chart);
    //this->setRenderHint(QPainter::Antialiasing); //抗锯齿
    this->setCursor(Qt::CrossCursor); //设置鼠标指针为十字星
    //创建折线
    series0 = new QLineSeries ();
    chart->addSeries(series0);
    //序列添加数值
    for (int t = beginPos; t <= endPos; t += Delta) {
        series0->append(t, dataBucket2[t]);
    }
    //创建坐标轴
    axisX = new QValueAxis; //X轴
    axisX->setRange(beginPos,endPos);
    axisX->setTitleText("time(secs)");
    axisY = new QValueAxis; //Y轴
    axisY->setRange(dataLow, dataHigh);
    axisY->setTitleText("value");
    chart->setAxisX(axisX, series0);
    chart->setAxisY(axisY, series0);

    //根据用户点击图例后，选择是否显示对应的曲线
    foreach (QLegendMarker* marker, chart->legend()->markers())
    {
        connect(marker, SIGNAL(clicked()), this, SLOT(on_LegendMarkerClicked()));
    }
}

void leftDownWidget::updateStaticChart() {
   //创建图表
    QChart * chart;
    chart = this->chart();
    //删除上一个曲线
    chart->removeSeries(series0);
    //创建折线
    series0 = new QLineSeries ();
    chart->addSeries(series0);
    //序列添加数值
    for (int t = beginPos; t <= endPos; t += Delta) {
        series0->append(t, dataBucket2[t]);
    }
    //删除之前的坐标轴
    chart->removeAxis(axisX);
    chart->removeAxis(axisY);
    //创建坐标轴
    axisX = new QValueAxis; //X轴
    axisX->setRange(beginPos,endPos);
    axisX->setTitleText("time(secs)");
    axisY = new QValueAxis; //Y轴
    axisY->setRange(dataLow, dataHigh);
    axisY->setTitleText("value");
    chart->setAxisX(axisX, series0);
    chart->setAxisY(axisY, series0);
}

void leftDownWidget::on_LegendMarkerClicked()
{//点击图例的marker的响应
    QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());

    switch (marker->type()) //marker的类型
    {
        case QLegendMarker::LegendMarkerTypeXY: //QLineSeries序列的图例marker
        {
            marker->series()->setVisible(!marker->series()->isVisible()); //可见性
            marker->setVisible(true);
            qreal alpha = 1.0;
            if (!marker->series()->isVisible())
                alpha = 0.5;

            QColor color;
            QBrush brush = marker->labelBrush();
            color = brush.color();
            color.setAlphaF(alpha);
            brush.setColor(color);
            marker->setLabelBrush(brush);

            brush = marker->brush();
            color = brush.color();
            color.setAlphaF(alpha);
            brush.setColor(color);
            marker->setBrush(brush);

            QPen pen = marker->pen();
            color = pen.color();
            color.setAlphaF(alpha);
            pen.setColor(color);
            marker->setPen(pen);
            break;
        }
        default:
            break;
    }
}

void leftDownWidget::on_mouseMovePoint(QPoint point)
{ //鼠标移动响应
    QPointF pt= this->chart()->mapToValue(point); //转换为图表的数值
   pa->labXYValue->setText(QString::asprintf("数据源=%d,X=%.2f,Y=%.2f",which+1,pt.x(),pt.y())); //状态栏显示
}

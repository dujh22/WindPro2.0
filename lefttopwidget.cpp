#include "lefttopwidget.h"
#include "global.h"
#include "mainwindow.h"
#include  "qwchartview.h"
#include <QDebug>
#include <QBarSet>

leftTopWidget::leftTopWidget(QWidget *parent) : QWChartView(parent) {
    // setMinimumSize(400,200);
    isexist0 = false;
    isexist1 = false;
    isexist2 = false;
    isexist3 = false;

    pa = (MainWindow *)parent;
}

void leftTopWidget::paintStaticChart() {
    //创建图表
    QChart * chart = new QChart();
    chart->setTitle(tr("数据源1源数据图像"));
    this->setChart(chart);

    //this->setRenderHint(QPainter::Antialiasing); //抗锯齿
    this->setCursor(Qt::CrossCursor); //设置鼠标指针为十字星
    //创建折线
    series0 = new QLineSeries ();
    chart->addSeries(series0);
    //序列添加数值
    for (int t = beginPos; t <= endPos; t += Delta) {
        series0->append(t, dataBucket1[t]);
    }
    /*
    //修改曲线颜色
    QColor color = series0->color();
    color=QColorDialog::getColor(color);
    if (color.isValid())
      series0->setColor(color);
    */
    //创建坐标轴
    axisX = new QValueAxis; //X轴
    axisX->setRange(beginPos,endPos);
    axisX->setTitleText("time(secs)");
    axisY = new QValueAxis; //Y轴
    axisY->setRange(dataLow, dataHigh);
    axisY->setTitleText("value");
    chart->setAxisX(axisX, series0);
    chart->setAxisY(axisY, series0);
    //qDebug() << "0";

    isexist0 = true;

    //根据用户点击图例后，选择是否显示对应的曲线
    foreach (QLegendMarker* marker, chart->legend()->markers())
    {
        connect(marker, SIGNAL(clicked()), this, SLOT(on_LegendMarkerClicked()));
    }
}

void leftTopWidget::updateStaticChart() {
   //创建图表
    QChart * chart;
    chart = this->chart();
    //删除上一个曲线
    if(isexist0)
        chart->removeSeries(series0);
    if(isexist1)
        chart->removeSeries(series1);
    if(isexist2)
        chart->removeSeries(series2);
    if(isexist3)
        chart->removeSeries(series3);
    //创建折线
    series0 = new QLineSeries ();
    chart->addSeries(series0);
    //序列添加数值
    for (int t = beginPos; t <= endPos; t += Delta) {
        series0->append(t, dataBucket1[t]);
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

    isexist0 = true;
}

void leftTopWidget::paint_data_delta() {
    //创建图表
     QChart * chart;
     chart = this->chart();
     chart->setTitle(" 相邻数据差状图");
     //删除上一个曲线
     if(isexist0)
         chart->removeSeries(series0);
     if(isexist1)
         chart->removeSeries(series1);
     if(isexist2)
         chart->removeSeries(series2);
     if(isexist3)
         chart->removeSeries(series3);

     //创建折线
     series0 = new QLineSeries ();
     chart->addSeries(series0);
     //序列添加数值
     double minD = 0, maxD = dataDelta1[0];
     for (unsigned int t = 0; t < dataDelta1.size(); t += Delta) {
         series0->append(t, dataDelta1[t]);
         if(dataDelta1[t] > maxD) {
             maxD = dataDelta1[t];
         } else if(dataDelta1[t] < minD) {
             minD = dataDelta1[t];
         }
     }

     //删除之前的坐标轴
     chart->removeAxis(axisX);
     chart->removeAxis(axisY);
     //创建坐标轴
     axisX = new QValueAxis; //X轴
     axisX->setRange(beginPos,endPos);
     axisX->setTitleText("time(secs)");
     axisY = new QValueAxis; //Y轴
     axisY->setRange(0, 5);
     axisY->setTitleText("value");
     chart->setAxisX(axisX, series0);
     chart->setAxisY(axisY, series0);

     isexist0 = true;
}

void leftTopWidget::bladetopbefore() {
   //创建图表
    QChart * chart;
    chart = this->chart();
    chart->setTitle(tr("数据源1叶片根部拟合前图像"));
    //删除上一个曲线
    if(isexist0)
        chart->removeSeries(series0);
    if(isexist1)
        chart->removeSeries(series1);
    if(isexist2)
        chart->removeSeries(series2);
    if(isexist3)
        chart->removeSeries(series3);
    //修改默认参数
    beginPos = 0;
    endPos = dataBucket11[0].size();
    Delta = 1;

    //创建折线
    series1 = new QLineSeries ();
    series2 = new QLineSeries ();
    series3 = new QLineSeries ();
    series4 = new QLineSeries ();
    series5 = new QLineSeries ();
    series6 = new QLineSeries ();


    //序列添加数值
//    for(int t = 0; t != dataBucket11[].size(); ++t) {
//        series1->append(t, dataBucket11[4][t]);
//    }
    for(int t = 0; t !=  dataBucket11[5].size(); ++t) {
        series2->append(t, dataBucket11[5][t]);
    }    
    for(int t = 0; t !=  dataBucket11[6].size(); ++t) {
        series3->append(t, dataBucket11[6][t]);
    }
    for(int t = 0; t != dataBucket11[7].size(); ++t) {
        series4->append(t, dataBucket11[7][t]);
    }
    for(int t = 0; t !=  dataBucket11[8].size(); ++t) {
        series5->append(t, dataBucket11[8][t]);
    }
    for(int t = 0; t !=  dataBucket11[9].size(); ++t) {
        series6->append(t, dataBucket11[9][t]);
    }
 //   chart->addSeries(series1);
    chart->addSeries(series2);
    chart->addSeries(series3);
    chart->addSeries(series4);
    chart->addSeries(series5);
    chart->addSeries(series6);
    //删除之前的坐标轴
    chart->removeAxis(axisX);
    chart->removeAxis(axisY);
    //创建坐标轴
    axisX = new QValueAxis; //X轴
    axisX->setRange(beginPos, endPos);
    axisX->setTitleText("序");
    axisY = new QValueAxis; //Y轴
    axisY->setRange(dataLow, dataHigh);
    axisY->setTitleText("值");
    chart->setAxisX(axisX, series1);
    chart->setAxisY(axisY, series1);

    isexist1 = true;
    isexist2 = true;
    isexist3 = true;
}

void leftTopWidget::on_LegendMarkerClicked()
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

void leftTopWidget::on_mouseMovePoint(QPoint point)
{ //鼠标移动响应
    QPointF pt= this->chart()->mapToValue(point); //转换为图表的数值
    pa->labXYValue->setText(QString::asprintf("数据源=%d,X=%.2f,Y=%.2f",which+1,pt.x(),pt.y())); //状态栏显示
}

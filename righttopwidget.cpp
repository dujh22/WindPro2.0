#include "righttopwidget.h"
#include "mainwindow.h"
#include "QWidget"

QWidget *tempww;

rightTopWidget::rightTopWidget(QWidget *parent) :
    QWidget(parent)
{
    tempww = parent;

    stackedWidget = new QStackedWidget(this);
    subpaintwidget = new subpaint;
    parameterswidget = new parametersWidget;
    conditionwidget = new conditionWidget;
    measuresetwidget = new measuresetWidget;
    pickwidget = new pickWidget;
    updatewidget = new updateWidget;  

    stackedWidget->addWidget(subpaintwidget);
    stackedWidget->addWidget(parameterswidget);
    stackedWidget->addWidget(conditionwidget);
    stackedWidget->addWidget(measuresetwidget);
    stackedWidget->addWidget(pickwidget);
    stackedWidget->addWidget(updatewidget);
    stackedWidget->setCurrentIndex(0);

}

void rightTopWidget::updateLeftTop() {
   ((MainWindow*)tempww)->updateLeftTop2();
}

void rightTopWidget::updateLeftDown() {
   ((MainWindow*)tempww)->updateLeftDown2();
}

void rightTopWidget::paint_data_delta() {
    ((MainWindow*)tempww)->paint_data_delta();
}

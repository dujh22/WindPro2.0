#include <QDebug>
#include <QStandardItemModel>
#include <QString>
#include <qmath.h>
#include "global.h"
#include "tablewidget.h"

tableWidget::tableWidget(QWidget* parent) : QTableView(parent) {
    _model = new QStandardItemModel(this);
   if(which == 0) {
       for (unsigned int i = 0; i < dataBucket1.size(); i++) {
           _model->setItem(i, 0, new QStandardItem(QString::number(dataBucket1[i])));
       }
   } else {
       for (unsigned int i = 0; i < dataBucket2.size(); i++) {
           _model->setItem(i, 0, new QStandardItem(QString::number(dataBucket2[i])));
       }
   }

    this->setFixedSize(400, 750);
    this->setModel(_model);
    //connect(_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(dataChangedSlot(QModelIndex,QModelIndex,QVector<int>)));
}
tableWidget::~tableWidget() {
}

//void tableWidget::dataChangedSlot(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles){
//    qDebug() << _model->data(topLeft).toString() << endl;
//}

void tableWidget:: update1(){
    QStandardItemModel* model = new QStandardItemModel(this);
    if(which == 0) {
        for (unsigned int i = 0; i < dataBucket1.size(); i++) {
            model->setItem(i, 0, new QStandardItem(QString::number(dataBucket1[i])));
        }
    } else {
        for (unsigned int i = 0; i < dataBucket2.size(); i++) {
            model->setItem(i, 0, new QStandardItem(QString::number(dataBucket2[i])));
        }
    }

    this->setModel(model);
    this->setFixedSize(400, 750);
}

void tableWidget:: slotitemChanged(QTableWidgetItem * item){
//    qDebug() << "运行到这里了";
         QString s=_model->item(item->row(),item->column())->text();
        if(which == 0)
             dataBucket1[item->row()]=s.toDouble();
        else
             dataBucket2[item->row()]=s.toDouble();
//        qDebug() << dataBucket[item->row()];
}


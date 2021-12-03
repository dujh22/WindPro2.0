#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>
#include <QString>

#include "subpaint.h"
#include "global.h"
#include "righttopwidget.h"
#include "mainwindow.h"



subpaint::subpaint(QWidget *parent) : QWidget(parent) {
    prighttop = (rightTopWidget *)parent;

    /*对象实例化*/
    upLabel = new QLabel(this);
    upLabel->setText("数据源1");
    up = new QRadioButton(this);
    up->setChecked(true);
    downLabel = new QLabel(this);
    downLabel->setText("数据源2");
    down = new QRadioButton(this);
    if(which == 0) {
        up->setChecked(true);
        down->setChecked(false);
    } else {
        up->setChecked(false);
        down->setChecked(true);
    }
    whichpaint = new QButtonGroup(this);
    whichpaint->addButton(up, 0);
    whichpaint->addButton(down, 1);

    maxLabel = new QLabel(this);
    maxLabel->setText(tr("最大值"));
    maxEdit = new QLineEdit("", this);
    maxEdit->setText(QString::number(DATAHIGH));
    minLabel = new QLabel(this);
    minLabel->setText(tr("最小值"));
    minEdit = new QLineEdit("", this);
    minEdit->setText(QString::number(DATALOW));
    beginpos = new QLabel(this);
    beginpos->setText("起始坐标");
    beginposEdit = new QLineEdit(this);
    beginposEdit->setText(QString::number(beginPos));
    endpos = new QLabel(this);
    endpos->setText("终止坐标");
    endposEdit = new QLineEdit(this);
    endposEdit->setText(QString::number(endPos));
    delta = new QLabel(this);
    delta->setText("坐标间隔");
    deltaEdit = new QLineEdit(this);
    deltaEdit->setText(QString::number(Delta));

    okButton = new QPushButton("确认", this);

    /*网格布局*/
    QGridLayout *subpaintLayout = new QGridLayout(this);
    subpaintLayout->addWidget(up, 0, 0);
    subpaintLayout->addWidget(upLabel, 0, 1);
    subpaintLayout->addWidget(down, 1, 0);
    subpaintLayout->addWidget(downLabel, 1, 1);
    subpaintLayout->addWidget(minLabel, 2, 0);
    subpaintLayout->addWidget(minEdit, 2, 1);
    subpaintLayout->addWidget(maxLabel, 3, 0);
    subpaintLayout->addWidget(maxEdit, 3, 1);
    subpaintLayout->addWidget(beginpos, 4, 0);
    subpaintLayout->addWidget(beginposEdit, 4, 1);
    subpaintLayout->addWidget(endpos, 5, 0);
    subpaintLayout->addWidget(endposEdit, 5, 1);
    subpaintLayout->addWidget(delta, 6, 0);
    subpaintLayout->addWidget(deltaEdit, 6, 1);
    subpaintLayout->addWidget(okButton, 7, 0);

    /*槽函数关联信号*/
    connect(okButton, SIGNAL(clicked()), this, SLOT(updatePaint()));
    connect(up, SIGNAL(clicked()), this, SLOT(setwhich()));
    connect(down, SIGNAL(clicked()), this, SLOT(setwhich()));
}

void subpaint::updatePaint() {
    int MAXPOS;
    if(down->isChecked()) {
        which = 1;
        MAXPOS = dataBucket2.size();
    } else {
        which = 0;
        MAXPOS = dataBucket1.size();
    }

    bool ok;
    QString dialog;
    int temp;
    double temp0;

    temp0 = minEdit->text().toDouble(&ok);
    if (ok == false) {
        dialog = "最小值设置无效\n";
        QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
        return;
    }
    dataLow = temp0;

    temp0 = maxEdit->text().toDouble(&ok);
    if (ok == false) {
        dialog = "最大值设置无效\n";
        QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
        return;
    }
    dataHigh = temp0;

    temp = beginposEdit->text().toInt(&ok);
    if(ok == false) {
        dialog = "起始坐标无效\n";
        QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
        return;
    } else {
        if(temp < 0) {
            dialog = "起始坐标不能<0\n";
            QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
            return;
        } else if(temp > MAXPOS) {
            QString ab = QString::number(MAXPOS);
            dialog = "起始坐标不超过" +  ab;
            QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
            return;
        }
    }
    beginPos = temp;

    temp = endposEdit->text().toInt(&ok);
    if(ok == false) {
        dialog = "终止坐标无效\n";
        QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
        return;
    } else {
        if(temp < 0) {
            dialog = "终止坐标不能<0\n";
            QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
            return;
        } else if(temp > MAXPOS) {
            QString ab = QString::number(MAXPOS);
            dialog = "终止坐标不超过" +  ab;
            QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
            return;
        } else if(temp <= beginPos) {
            dialog = "终止坐标需大于起始坐标";
            QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
            return;
        }
    }
    endPos = temp;

    temp = deltaEdit->text().toInt(&ok);
    MAXPOS = endPos - beginPos;
    if(ok == false) {
        dialog = "坐标间隔无效\n";
        QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
        return;
    } else {
        if(temp < 0) {
            dialog = "坐标间隔不能<0\n";
            QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
            return;
        } else if(temp > MAXPOS) {
            QString ab = QString::number(MAXPOS);
            dialog = "坐标间隔不超过" +  ab;\
            QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
            return;
        }
    }
    Delta = temp;

    if(which == 0) { //刷新上图
        prighttop->updateLeftTop();
    } else { //刷新下图
        prighttop->updateLeftDown();
    }
}

void subpaint::setwhich() {
    if(up->isChecked()) {
        which = 0;
        QMessageBox::information(this, "提示", "已选择数据源1", QMessageBox::Ok);
    } else {
        which = 1;
        QMessageBox::information(this, "提示", "已选择数据源2", QMessageBox::Ok);
    }
}

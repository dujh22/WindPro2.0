#include <QGridLayout>
#include <QMessageBox>

#include "conditionwidget.h"
#include "global.h"
using namespace std;

conditionWidget::conditionWidget(QWidget *parent) : QWidget(parent) {
    /*对象实例化*/
    itemNameLabel = new QLabel(this);
    itemNameLabel->setText("测量项目名称");
    itemNameEdit = new QLineEdit(this);
    dataNameLabel = new QLabel(this);
    dataNameLabel->setText("测量数据名称");
    dataNameEdit = new QLineEdit(this);
    beginTimeLabel = new QLabel(this);
    beginTimeLabel->setText("测量开始时间");
    beginTimeEdit = new QLineEdit(this);
    endTimeLabel = new QLabel(this);
    endTimeLabel->setText("测量结束时间");
    endTimeEdit = new QLineEdit(this);
    confirmButton = new QPushButton("确认", this);

    /*网格布局*/
    QGridLayout *conditionLayout = new QGridLayout(this);
    conditionLayout->addWidget(itemNameLabel, 0, 0);
    conditionLayout->addWidget(itemNameEdit, 0, 1);
    conditionLayout->addWidget(dataNameLabel, 1, 0);
    conditionLayout->addWidget(dataNameEdit, 1, 1);
    conditionLayout->addWidget(beginTimeLabel, 2, 0);
    conditionLayout->addWidget(beginTimeEdit, 2, 1);
    conditionLayout->addWidget(endTimeLabel, 3, 0);
    conditionLayout->addWidget(endTimeEdit, 3, 1);
    conditionLayout->addWidget(confirmButton, 4, 1);

    /*槽函数关联信号*/
    connect(confirmButton, SIGNAL(clicked()), this, SLOT(sendInfo()));
}

void conditionWidget::sendInfo() {
    string tempname;
    double tempnum;
    bool ok;
    QString dialog;
    tempname = itemNameEdit->text().toStdString();
    itemName = tempname;
    tempname = dataNameEdit->text().toStdString();
    dataName = tempname;
    tempnum = beginTimeEdit->text().toDouble(&ok);
    if (ok == false) {
        dialog = "测量开始时间数据无效\n";
        QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
        return;
    }
    beginTime = tempnum;
    tempnum = endTimeEdit->text().toDouble(&ok);
    if (ok == false) {
        dialog = "测量结束时间数据无效\n";
        QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
        return;
    }
    endTime = tempnum;
    dialog = "信息设置成功\n";
    QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
}

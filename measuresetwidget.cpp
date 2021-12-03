#include "measuresetwidget.h"
#include <QGridLayout>
#include <QMessageBox>
#include "global.h"

measuresetWidget::measuresetWidget(QWidget *parent) : QWidget(parent) {
    /*对象实例化*/
    aAngleLabel = new QLabel(this);
    aAngleLabel->setText("叶根传感器测量倾角(弧度制)");
    aAngleEdit = new QLineEdit(this);
    bAngelLabel = new QLabel(this);
    bAngelLabel->setText("叶尖传感器测量倾角(弧度制)");
    bAngleEdit = new QLineEdit(this);
    confirmButton = new QPushButton("确认", this);
    /*网格布局*/
    QGridLayout *measuresetLayout = new QGridLayout(this);
    measuresetLayout->addWidget(aAngleLabel, 0, 0);
    measuresetLayout->addWidget(aAngleEdit, 0, 1);
    measuresetLayout->addWidget(bAngelLabel, 1, 0);
    measuresetLayout->addWidget(bAngleEdit, 1, 1);
    measuresetLayout->addWidget(confirmButton, 6, 1);

    /*槽函数关联信号*/
    connect(confirmButton, SIGNAL(clicked()), this, SLOT(sendInfo()));
}

void measuresetWidget::sendInfo()
{
    double temp;
    bool ok;
    QString dialog;
    temp = aAngleEdit->text().toDouble(&ok);
    if (ok == false) {
        dialog = "叶根传感器测量倾角数据无效\n";
        QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
        return;
    }
    aAngle = temp;
    temp = bAngleEdit->text().toDouble(&ok);
    if (ok == false) {
        dialog = "叶尖传感器测量倾角数据无效\n";
        QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
        return;
    }
    bAngle = temp;
    dialog = "信息设置成功\n";
    QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
}

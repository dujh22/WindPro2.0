#include <QGridLayout>
#include <QMessageBox>

#include "global.h"
#include "parameterswidget.h"

parametersWidget::parametersWidget(QWidget *parent) : QWidget(parent) {
    /*对象实例化*/
    rootFrequencyLabel = new QLabel(this);
    rootFrequencyLabel->setText("叶根测量频率(Hz)");
    rootFrequencyEdit = new QLineEdit(this);
    //    rootAcceptPortLabel=new QLabel(this);
    //    rootAcceptPortLabel->setText("叶根数据接收端口");
    //    rootAcceptPortEdit=new QLineEdit(this);
    //    rootTransmissionRateLabel=new QLabel(this);
    //    rootTransmissionRateLabel->setText("叶根数据传输频率");
    //    rootTransmissionRateEdit=new QLineEdit(this);
    tipFrequencyLabel = new QLabel(this);
    tipFrequencyLabel->setText("叶尖测量频率(Hz)");
    tipFrequencyEdit = new QLineEdit(this);
    //    tipAcceptPortLabel=new QLabel(this);
    //    tipAcceptPortLabel->setText("叶尖数据接收端口");
    //    tipAcceptPortEdit=new QLineEdit(this);
    //    tipTransmissionRateLabel=new QLabel(this);
    //    tipTransmissionRateLabel->setText("叶尖数据传输频率");
    //    tipTransmissionRateEdit=new QLineEdit(this);
    confirmButton = new QPushButton("确认", this);

    /*网格布局*/
    QGridLayout *parametersLayout = new QGridLayout(this);
    parametersLayout->addWidget(rootFrequencyLabel, 0, 0);
    parametersLayout->addWidget(rootFrequencyEdit, 0, 1);
    //    parametersLayout->addWidget(rootAcceptPortLabel,1,0);
    //    parametersLayout->addWidget(rootAcceptPortEdit,1,1);
    //    parametersLayout->addWidget(rootTransmissionRateLabel,2,0);
    //    parametersLayout->addWidget(rootTransmissionRateEdit,2,1);
    parametersLayout->addWidget(tipFrequencyLabel, 3, 0);
    parametersLayout->addWidget(tipFrequencyEdit, 3, 1);
    //    parametersLayout->addWidget(tipAcceptPortLabel,4,0);
    //    parametersLayout->addWidget(tipAcceptPortEdit,4,1);
    //    parametersLayout->addWidget(tipTransmissionRateLabel,5,0);
    //    parametersLayout->addWidget(tipTransmissionRateEdit,5,1);
    parametersLayout->addWidget(confirmButton, 6, 1);

    /*槽函数关联信号*/
    connect(confirmButton, SIGNAL(clicked()), this, SLOT(sendInfo()));
}

void parametersWidget::sendInfo() {
    double temp;
    bool ok;
    QString dialog;
    temp = rootFrequencyEdit->text().toDouble(&ok);
    if (ok == false) {
        dialog = "叶根频率数据无效\n";
        QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
        return;
    }
    rootFrequency = temp;
    temp = tipFrequencyEdit->text().toDouble(&ok);
    if (ok == false) {
        dialog = "叶尖频率数据无效\n";
        QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
        return;
    }
    tipFrequency = temp;
    dialog = "信息设置成功\n";
    QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
}

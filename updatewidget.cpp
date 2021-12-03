#include <QGridLayout>
#include <QMessageBox>

#include "global.h"
#include "updatewidget.h"
updateWidget::updateWidget(QWidget *parent) : QWidget(parent) {
    updateLabel = new QLabel(this);
    updateLabel->setText(tr("修改数据"));
    updateEdit = new QLineEdit("", this);
    posLabel = new QLabel(this);
    posLabel->setText(tr("修改位置"));
    posEdit = new QLineEdit("",this);
    updateButton = new QPushButton(tr("确定"), this); 
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(posLabel, 0, 0);
    mainLayout->addWidget(posEdit, 0, 1);
    mainLayout->addWidget(updateLabel,1,0);
    mainLayout->addWidget(updateEdit,1,1);
    mainLayout->addWidget(updateButton, 2, 1);
    setLayout(mainLayout);
    connect(updateButton, SIGNAL(clicked()), this, SLOT(sendInfo()));
}
void updateWidget::sendInfo() {
    bool ok;
    QString dialog;
    double temp = posEdit->text().toDouble(&ok);
    if (ok == false) {
        dialog = "位置输入无效\n";
        QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
        return;
    }
    temp = updateEdit->text().toDouble(&ok);
    if (ok == false) {
        dialog = "修改数据无效\n";
        QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
        return;
    }
    doUpdate();
    dialog = "修改设置成功\n";
    QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
}
void updateWidget::doUpdate(){

}

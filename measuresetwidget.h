#ifndef MEASURESETWIDGET_H
#define MEASURESETWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QTextCodec>
#include <QPushButton>

class measuresetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit measuresetWidget(QWidget *parent = nullptr);

signals:

public slots:
    void sendInfo();
private:
    QLabel *aAngleLabel;
    QLineEdit *aAngleEdit;
    QLabel *bAngelLabel;
    QLineEdit *bAngleEdit;
    /*确认按钮*/
    QPushButton *confirmButton;
};

#endif // MEASURESETWIDGET_H

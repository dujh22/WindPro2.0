#ifndef CONDITIONWIDGET_H
#define CONDITIONWIDGET_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextCodec>
#include <QWidget>

class conditionWidget : public QWidget {
    Q_OBJECT
   public:
    explicit conditionWidget(QWidget *parent = nullptr);
   signals:

   public slots:
    void sendInfo();

   private:
    QLabel *itemNameLabel;
    QLineEdit *itemNameEdit;
    QLabel *dataNameLabel;
    QLineEdit *dataNameEdit;
    QLabel *beginTimeLabel;
    QLineEdit *beginTimeEdit;
    QLabel *endTimeLabel;
    QLineEdit *endTimeEdit;
    /*确认按钮*/
    QPushButton *confirmButton;
};

#endif  // CONDITIONWIDGET_H

#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextCodec>
#include <QWidget>

class parametersWidget : public QWidget {
    Q_OBJECT
   public:
    explicit parametersWidget(QWidget *parent = nullptr);

   private:
    /*叶根的相关*/
    QLabel *rootFrequencyLabel;
    QLineEdit *rootFrequencyEdit;
    //    QLabel *rootAcceptPortLabel;
    //    QLineEdit *rootAcceptPortEdit;
    //    QLabel *rootTransmissionRateLabel;
    //    QLineEdit *rootTransmissionRateEdit;
    /*叶尖相关*/
    QLabel *tipFrequencyLabel;
    QLineEdit *tipFrequencyEdit;
    //    QLabel *tipAcceptPortLabel;
    //    QLineEdit *tipAcceptPortEdit;
    //    QLabel *tipTransmissionRateLabel;
    //    QLineEdit *tipTransmissionRateEdit;
    /*确认按钮*/
    QPushButton *confirmButton;
   signals:
   public slots:
    void sendInfo();
};

#endif  // PARAMETERSWIDGET_H

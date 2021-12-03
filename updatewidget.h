#ifndef UPDATEWIDGET_H
#define UPDATEWIDGET_H
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextCodec>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
class updateWidget : public QWidget {
    Q_OBJECT
public:
    explicit updateWidget(QWidget *parent = nullptr);
    void doUpdate();
public slots:
    void sendInfo();

private:
    QPushButton *updateButton;
    QLabel *updateLabel;
    QLabel *posLabel;
    QLineEdit *updateEdit;
    QLineEdit *posEdit;
};

#endif  // UPDATEWIDGET_H

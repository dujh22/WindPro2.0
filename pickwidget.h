#ifndef PICKWIDGET_H
#define PICKWIDGET_H
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextCodec>
#include <QTextEdit>
#include <QWidget>
class rightTopWidget;

class pickWidget : public QWidget {
    Q_OBJECT
   public:
    explicit pickWidget(QWidget *parent = nullptr);
    void pick(); //1.初步筛选调用的子函数：将大于最大值和小于最小值的数据修改为1
    void correct(); //2.纠错调用子函数
    void finddifference(); //3.求差值子函数
    void dataclass(); //4.数据分类
   public slots:
    void sendInfo(); //1.输入人为给定的最大值和最小值，进行初步筛选
    void sendInfo1(); //2.纠错
    void sendInfo2(); //3.求差值
    void sendInfo3(); //4.分类
   private:
    QPushButton *pickButton;
    QPushButton *correctButton;
    QPushButton *finddifferenceButton;
    QPushButton *dataclassButton;
    QLabel *maxLabel;
    QLabel *minLabel;
    QLineEdit *maxEdit;
    QLineEdit *minEdit;
    rightTopWidget * prighttop;
};

#endif  // PICKWIDGET_H

#ifndef SUBPAINT_H
#define SUBPAINT_H

#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
class rightTopWidget;

class subpaint : public QWidget
{
    Q_OBJECT
public:
    explicit subpaint(QWidget *parent = nullptr);

signals:

public slots:
    void updatePaint();         //重新绘制图像
    void setwhich();
private:
    QButtonGroup *whichpaint;    //选择要查看的是哪个子图
    QRadioButton *up;            //选择上图
    QRadioButton *down;          //选择下图
    QLabel *upLabel;
    QLabel *downLabel;
    QLabel *beginpos;            //起始坐标
    QLabel *endpos;              //终止坐标
    QLabel *maxLabel;     //纵坐标最大值
    QLabel *minLabel;     //纵坐标最小值
    QLabel *delta;               //间隔
    QLineEdit *beginposEdit;     //输入起始坐标
    QLineEdit *endposEdit;       //输入终止坐标
    QLineEdit *deltaEdit;        //输入中间间隔
    QLineEdit *maxEdit;         //输入纵坐标最大值
    QLineEdit *minEdit;         //输入纵坐标最小值
    QPushButton *okButton;       //确认按钮：更新图示
    rightTopWidget * prighttop;
};

#endif // SUBPAINT_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <vector>
#include <QPixmap>
#include <QLabel>
#include <QToolBar>
#include "leftdownwidget.h"
#include "lefttopwidget.h"
#include "rightdownwidget.h"
#include "righttopwidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
     void updateLeftTop2();
     void updateLeftDown2();
     void paint_data_delta();
     QLabel  *labXYValue; //状态栏显示文字标签

private:
    QPixmap pixmap;

    leftTopWidget *leftTop;
    leftDownWidget *leftDown;
    rightTopWidget *rightTop;
    rightDownWidget *rightDown;

    QSplitter *splitterMain;
    QSplitter *splitterRight;
    QSplitter *splitterLeft;

    QMenu *fileMenu;
    QMenu *setMenu;
    QMenu *measureMessageMenu;
    QMenu *measureFunctionMenu;
    QMenu *viewActionMenu;
    QMenu *relateActionMenu;

    QAction *newBuiltAction;
    QAction *openAction1;
    QAction *openAction2;
    QAction *addaction;
    QAction *saveAction;
    QAction *repoartAction;
    QAction *exitAction;

    QAction *parametersAction;
    QAction *conditionAction;
    QAction *measuresetAction;

    //QAction *recieveAction;
    QAction *pickAction;
    //QAction *viewAction;
    QAction *updateAction;

    QAction *bladeAngleAction;
    QAction *bladeTwistAction;
    QAction *bladePitchAction;
    QAction *towerVibrationAction;
    QAction *fanClearanceAction;
    QAction *bladeDeflectionAction;
    QAction *yawDetectionAction;
    QAction *bladetopbeforeAction;
    QAction *bladetopbehindAction;
    QAction *bladerootbeforeAction;
    QAction *bladerootbehindAction;

    QAction *basicAction;
    QAction *enlargeAction;
    QAction *shrinkAction;
    QAction *iniAction;

    QAction *softwareVersionAction;
    QAction *technicalSupportAction;

    QToolBar *ToolBar;

private slots:
    void newBuilt();
    void open1();
    void open2();
    void add();
    void save();
    void repoart();
    void parameters();  //风机信息
    void condition();   //条件信息
    void measureset();  //数据信息
    //void recieve();
    void pick();
    //void view();
    void update();
    void bladeAngle();
    void bladeTwist();
    void bladePitch();
    void towerVibration();
    void fanClearance();
    void bladeDeflection();
    void yawDetection();
    void basic();
    void enlarge();
    void shrink();
    void iniSize();
    void bladetopbefore();
    void bladetopbehind();
    void bladerootbefore();
    void bladerootbehind();
    void softwareVersion();
    void technicalSupport();

    void on_mouseMovePoint(QPoint point); //鼠标移动事件，自定义槽函数
};

#endif  // MAINWINDOW_H

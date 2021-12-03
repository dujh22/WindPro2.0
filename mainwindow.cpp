#include <time.h>
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QStackedWidget>
#include <QTextStream>
#include <ctime>
#include <QDebug>
#include "global.h"
#include "leftdownwidget.h"
#include "lefttopwidget.h"
#include "mainwindow.h"
#include "rightdownwidget.h"
#include "righttopwidget.h"
#include "tablewidget.h"

using namespace std;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    setWindowTitle("风力发电机气动平衡检测系统");
    setWindowIcon(QIcon(":/new/prefix1/ico"));

    QDesktopWidget* desktop = QApplication::desktop();
    //      resize(desktop->width()/2,desktop->height()/2);
    //      move(desktop->width()/2-this->width()/2,desktop->height()/2-this->height()/2);
    setWindowFlag(Qt::Window);
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
    setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);
    setWindowState(Qt::WindowMaximized);
    //    setFixedSize();
    //    showFullScreen();
    this->setFixedSize(desktop->width(),desktop->height());
    //设置其界面为最大值

    //设置切分
    splitterMain = new QSplitter(Qt::Horizontal, this);  //水平划分
    splitterLeft = new QSplitter(Qt::Vertical, this);
    splitterRight = new QSplitter(Qt::Vertical, this);

    leftDown = new leftDownWidget(this);
    leftTop = new leftTopWidget(this);
    rightTop = new rightTopWidget(this);
    rightDown = new rightDownWidget(this);
    leftDown->setStyleSheet("background-color:white;");
    leftTop->setStyleSheet("background-color:white;");
    rightTop->setStyleSheet("background-color:white;");
    rightDown->setStyleSheet("background-color:white;");

    splitterLeft->setOpaqueResize(false);
    splitterRight->setOpaqueResize(false);
    splitterLeft->addWidget(leftTop);
    splitterLeft->addWidget(leftDown);
    splitterRight->addWidget(rightTop);
    splitterRight->addWidget(rightDown);

    splitterRight->setMinimumSize(400, 200);
    splitterRight->setStretchFactor(0,1);
    splitterRight->setStretchFactor(1,3);

    splitterLeft->setStretchFactor(0,-1);
    splitterLeft->setStretchFactor(1,-1);
    //应该会使得控件不可伸缩

    splitterMain->addWidget(splitterLeft);
    splitterMain->addWidget(splitterRight);
    splitterMain->setStyleSheet("QSplitter::handle { background-color: gray }");
    splitterLeft->setStyleSheet("QSplitter::handle { background-color: gray }");
    splitterRight->setStyleSheet("QSplitter::handle { background-color: gray }");
    splitterMain->setHandleWidth(1);
    splitterLeft->setHandleWidth(1);
    splitterRight->setHandleWidth(1);
    splitterMain->setOpaqueResize(false);
    splitterMain->setStretchFactor(0, 1);

    this->setCentralWidget(splitterMain);
    //切分完毕

    fileMenu = menuBar()->addMenu(tr("项目"));
    setMenu = menuBar()->addMenu(tr("参数信息"));
    measureMessageMenu = menuBar()->addMenu(tr("测量数据"));
    measureFunctionMenu = menuBar()->addMenu(tr("测量功能"));
    viewActionMenu = menuBar()->addMenu(tr("视图"));
    relateActionMenu = menuBar()->addMenu(tr("关于"));
    //添加菜单

//    newBuiltAction = new QAction(tr("新建"), this);
//    fileMenu->addAction(newBuiltAction);
    openAction1 = new QAction(QIcon("open1.gif"), tr("打开数据源1"), this);
    fileMenu->addAction(openAction1);
    openAction1->setShortcut(tr("Ctrl+O"));
    openAction1->setStatusTip(tr("打开数据源1文件"));
    openAction2 = new QAction(QIcon("open2.gif"), tr("打开数据源2"), this);
    fileMenu->addAction(openAction2);
    openAction2->setShortcut(tr("Ctrl+P"));
    openAction2->setStatusTip(tr("打开数据源2文件"));
//    addaction = new QAction(tr("添加"), this);
//    fileMenu->addAction(addaction);
    saveAction = new QAction(QIcon("save.gif"), tr("保存"), this);
    fileMenu->addAction(saveAction);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("保存指定数据源数据"));
    repoartAction = new QAction(QIcon("file.gif"), ("报告"), this);
    fileMenu->addAction(repoartAction);
    repoartAction->setShortcut(tr("Ctrl+R"));
    repoartAction->setStatusTip(tr("输出分析报告"));
    exitAction = new QAction(tr("退出"), this);
    fileMenu->addAction(exitAction);
    //文件操作QAction

    parametersAction = new QAction(tr("传输信息"), this);
    setMenu->addAction(parametersAction);
    conditionAction = new QAction(tr("测量信息"), this);
    setMenu->addAction(conditionAction);
    measuresetAction = new QAction(tr("角度信息"), this);
    setMenu->addAction(measuresetAction);
    //setMenu->setStyleSheet("background-color:white;");
    //参数设置QAction

    pickAction = new QAction(tr("筛选"), this);
    measureMessageMenu->addAction(pickAction);
    updateAction = new QAction(tr("修改"), this);
    //measureMessageMenu->setStyleSheet("background-color:white;");
    //测量数据QAction

    measureMessageMenu->addAction(updateAction);
    bladeAngleAction = new QAction(tr("叶片偏角-无"), this);
    measureFunctionMenu->addAction(bladeAngleAction);
    bladeTwistAction = new QAction(tr("叶片扭曲-无"), this);
    measureFunctionMenu->addAction(bladeTwistAction);
    bladePitchAction = new QAction(tr("叶片齿距-无"), this);
    measureFunctionMenu->addAction(bladePitchAction);
    towerVibrationAction = new QAction(tr("塔筒震动-无"), this);
    measureFunctionMenu->addAction(towerVibrationAction);
    fanClearanceAction = new QAction(tr("风机净空-无"), this);
    measureFunctionMenu->addAction(fanClearanceAction);
    bladeDeflectionAction = new QAction(tr("叶片挠度-无"), this);
    measureFunctionMenu->addAction(bladeDeflectionAction);
    yawDetectionAction = new QAction(tr("偏航检测-无"),this);
    measureFunctionMenu->addAction(yawDetectionAction);
    bladetopbeforeAction = new QAction(tr("叶片尖部拟合前-目前可成图"), this);
    bladetopbeforeAction->setStatusTip(tr("注意：请确保已经完成测试数据的筛选"));
    measureFunctionMenu->addAction(bladetopbeforeAction);
    bladetopbehindAction = new QAction(tr("叶片尖部拟合后-无"), this);
    measureFunctionMenu->addAction(bladetopbehindAction);
    bladerootbeforeAction = new QAction(tr("叶片根部拟合前-无"), this);
    measureFunctionMenu->addAction(bladerootbeforeAction);
    bladerootbehindAction = new QAction(tr("叶片根部拟合后-无"), this);
    measureFunctionMenu->addAction(bladerootbehindAction); 
    measureFunctionMenu->addAction(yawDetectionAction);
    //measureFunctionMenu->setStyleSheet("background-color:white;");
    //测量功能QAction

    basicAction = new QAction(tr("基本参数"), this);
    viewActionMenu->addAction(basicAction);
    enlargeAction = new QAction(QIcon("enlarge.bmp"), tr("放大"), this);
    enlargeAction->setShortcut(tr("Ctrl+E"));
    enlargeAction->setStatusTip(tr("局部放大"));
    viewActionMenu->addAction(enlargeAction);
    shrinkAction = new QAction(QIcon("shrink.bmp"), tr("缩小"), this);
    shrinkAction->setShortcut(tr("Ctrl+S"));
    shrinkAction->setStatusTip(tr("局部缩小"));
    viewActionMenu->addAction(shrinkAction);
    iniAction = new QAction(QIcon("ini.bmp"), tr("原始大小"), this);
    iniAction->setShortcut(tr("Ctrl+I"));
    iniAction->setStatusTip(tr("还原并浏览全图"));
    viewActionMenu->addAction(iniAction);
    //viewActionMenu->setStyleSheet("background-color:white;");
     //放大缩小QAction

    ToolBar = addToolBar(tr("Draw"));
    ToolBar->setStyleSheet("background-color:white;");
    ToolBar->addAction(openAction1);
    ToolBar->addAction(openAction2);
    ToolBar->addAction(saveAction);
    ToolBar->addAction(repoartAction);
    ToolBar->addSeparator();
    ToolBar->addAction(enlargeAction);
    ToolBar->addAction(shrinkAction);
    ToolBar->addAction(iniAction);
    //添加快捷菜单

    softwareVersionAction = new QAction(tr("软件版本"), this);
    relateActionMenu->addAction(softwareVersionAction);
    technicalSupportAction = new QAction(tr("技术支持"), this);
    relateActionMenu->addAction(technicalSupportAction);
    //relateActionMenu->setStyleSheet("background-color:white;");

    //关联信号槽
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));//关闭
    connect(openAction1, SIGNAL(triggered()), this, SLOT(open1()));//打开数据源1
    connect(openAction2, SIGNAL(triggered()), this, SLOT(open2()));//打开数据源1
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));//保存
    connect(repoartAction, SIGNAL(triggered()), this, SLOT(repoart()));//生成报告
    connect(parametersAction, SIGNAL(triggered()), this, SLOT(parameters()));//测试条件
    connect(conditionAction, SIGNAL(triggered()), this, SLOT(condition()));//风机参数
    connect(measuresetAction, SIGNAL(triggered()), this, SLOT(measureset()));//测量设置
    connect(pickAction, SIGNAL(triggered()), this, SLOT(pick()));//筛选
    connect(updateAction, SIGNAL(triggered()), this, SLOT(update()));//修改
    connect(bladeAngleAction, SIGNAL(triggered()), this, SLOT(bladeAngle()));//叶片偏角
    connect(bladeTwistAction, SIGNAL(triggered()), this, SLOT(bladeTwist()));//叶片扭角
    connect(bladePitchAction, SIGNAL(triggered()), this, SLOT(bladePitch()));//叶片齿距
    connect(towerVibrationAction, SIGNAL(triggered()), this, SLOT(towerVibration()));//塔筒振动
    connect(fanClearanceAction, SIGNAL(triggered()), this, SLOT(fanClearance()));//风机震动
    connect(bladeDeflectionAction, SIGNAL(triggered()), this, SLOT(bladeDeflection()));//叶片挠度
    connect(yawDetectionAction, SIGNAL(triggered()), this, SLOT(yawDetection()));//偏航检测
    connect(bladetopbeforeAction, SIGNAL(triggered()), this, SLOT(bladetopbefore()));//叶片尖部拟合前
    connect(bladetopbehindAction, SIGNAL(triggered()), this, SLOT(bladetopbehind()));//叶片尖部拟合后
    connect(bladerootbeforeAction, SIGNAL(triggered()), this, SLOT(bladerootbefore()));//叶片根部拟合前
    connect(bladerootbehindAction, SIGNAL(triggered()), this, SLOT(bladerootbehind()));//叶片根部拟合后

    connect(basicAction, SIGNAL(triggered()), this, SLOT(basic()));
    connect(enlargeAction, SIGNAL(triggered()), this, SLOT(enlarge()));
    connect(shrinkAction, SIGNAL(triggered()), this, SLOT(shrink()));
    connect(iniAction, SIGNAL(triggered()), this, SLOT(iniSize()));

    connect(softwareVersionAction, SIGNAL(triggered()), this, SLOT(softwareVersion()));
    connect(technicalSupportAction, SIGNAL(triggered()), this, SLOT(technicalSupport()));

    QObject::connect(this->leftTop, SIGNAL(mouseMovePoint(QPoint)),
                     this, SLOT(on_mouseMovePoint(QPoint)));  //鼠标移动事件
    QObject::connect(this->leftDown, SIGNAL(mouseMovePoint(QPoint)),
                     this, SLOT(on_mouseMovePoint(QPoint)));  //鼠标移动事件

    //添加左下角坐标子标注
    labXYValue = new QLabel("数据源=，X=,  Y=  "); //状态栏显示鼠标点的坐标
    labXYValue->setMinimumWidth(300);
    this->statusBar()->addPermanentWidget(labXYValue);
    this->statusBar()->setStyleSheet("background-color:white;");

}

MainWindow::~MainWindow() {

}
void MainWindow::newBuilt() {
}

void MainWindow::open1() {
    //获取文件路径来打开文件，并检验文件是否打开。否则直接return
    QString fileName = QFileDialog::getOpenFileName(this, tr("打开文件"),
                                                    ".", tr("txt Files (*.txt)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(NULL, tr("警告！"), tr("未打开任何文件"));
        return;
    }
    //创建一个QtextStream对象来操纵file
    QTextStream fin(&file);
    double tem;
    time_t tv = time(0);
    //当QtextStream对象没有到末尾时，循环
    bool ok = false;
    while (!fin.atEnd()){
        //取得文件中的字符串
        QString s;
        fin >> s;
        tem = s.toDouble(&ok);
        if(!ok){
            //转换失败
            if(s == "D") tem = 0;//标志位的无效数据
            else if(s == "DE02") tem = 1;//错误的无效数据
            else tem = -1;//以-1代表无效数据

        }
        tv = time(0);
        timeStamp.push_back(tv);
        if(tem != 0)
        dataBucket1.push_back(tem);
//        qDebug() << temp << " " << tv;
    }
    file.close();
    this->leftTop->paintStaticChart();
    rightDown->tablewidget->update1();
}

void MainWindow::open2() {
    //获取文件路径来打开文件，并检验文件是否打开。否则直接return
    QString fileName = QFileDialog::getOpenFileName(this, tr("打开文件"), ".", tr("txt Files (*.txt)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(NULL, tr("警告！"), tr("未打开任何文件"));
        return;
    }
    //创建一个QtextStream对象来操纵file
    QTextStream fin(&file);
    double tem;
    time_t tv = time(0);
    //当QtextStream对象没有到末尾时，循环
    bool ok = false;
    while (!fin.atEnd()){
        //取得文件中的字符串
        QString s;
        fin >> s;
        tem = s.toDouble(&ok);
        if(!ok){
            //转换失败
            if(s == "D") tem = 0;//标志位的无效数据
            else if(s == "DE02") tem = 1;//错误的无效数据
            else tem = -1;//以-1代表无效数据
        }
        tv = time(0);
        timeStamp.push_back(tv);
        if(tem != 0)
        dataBucket2.push_back(tem);
//        qDebug() << temp << " " << tv;
    }
    file.close();
    this->leftDown->paintStaticChart();
    //rightDown->tablewidget->update1();
}

void MainWindow::add() {
}

void MainWindow::save() {
    // 获取文件路径来打开文件，并检验文件是否打开。否则直接return
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存文件"),
                                                    ".", tr("txt Files (*.txt)"));
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(NULL, tr("警告！"), tr("未成功保存！"));
        return;
    }

    // 创建一个QtextStream对象来操纵file
    QTextStream fout(&file);

    vector<double>::iterator itData;
    if(which == 0) {
        itData = dataBucket1.begin();
        //    vector<int>::iterator itTime = timeStamp.begin();
        //时间函数不知道需不需要保存
        for(;itData != dataBucket1.end();++itData){
            fout << *itData << endl;
        }
    } else {
        itData = dataBucket2.begin();
        //    vector<int>::iterator itTime = timeStamp.begin();
        //时间函数不知道需不需要保存
        for(;itData != dataBucket2.end();++itData){
            fout << *itData << endl;
        }
    }

    file.close();
    QMessageBox::information(NULL,tr("提示！"),tr("成功保存！"));
}

void MainWindow::repoart() {
}

void MainWindow::basic() {
    rightTop->stackedWidget->setCurrentIndex(0);
}

void MainWindow::parameters() {//风机信息
    rightTop->stackedWidget->setCurrentIndex(1);
}

void MainWindow::condition() {//条件信息
    rightTop->stackedWidget->setCurrentIndex(2);
}

void MainWindow::measureset() {//数据信息
    rightTop->stackedWidget->setCurrentIndex(3);
}

//void MainWindow::recieve(){

//}

void MainWindow::pick() {
    //筛选
    rightTop->stackedWidget->setCurrentIndex(4);
}

//void MainWindow:: view(){

//}

void MainWindow::update() {
    rightTop->stackedWidget->setCurrentIndex(5);
}

void MainWindow::bladeAngle() {
    //叶片偏角
}

void MainWindow::bladeTwist() {
    //叶片扭角
}

void MainWindow::bladePitch() {
    //叶片齿距
}

void MainWindow::towerVibration() {
    //塔筒振动
}

void MainWindow::fanClearance() {
    //风机净空
}

void MainWindow::bladeDeflection() {
    //叶尖挠度
}

void MainWindow::yawDetection() {
    //偏航检测
}

void MainWindow::enlarge() {
    //图片的放大功能
    if(which == 0) {
        this->leftTop->chart()->zoom(1.2);
    } else {
        this->leftDown->chart()->zoom(1.2);
    }
}

void MainWindow::shrink() {
    //图片的缩小功能
    if(which == 0) {
        this->leftTop->chart()->zoom(0.8);
    } else {
        this->leftDown->chart()->zoom(0.8);
    }
}

void MainWindow::iniSize() {
    //图片恢复原始大小
    if(which == 0) {
        this->leftTop->chart()->zoomReset();;
    } else {
        this->leftDown->chart()->zoomReset();
    }
}

void MainWindow::bladetopbefore(){
    //叶片尖部拟合前成图
        leftTop->bladetopbefore();
}

void MainWindow::bladetopbehind(){
    //叶片尖部拟合后成图
}
void MainWindow::bladerootbefore(){
    //叶片根部拟合前成图

}
void MainWindow::bladerootbehind(){
    //叶片根部拟合后成图
}


void MainWindow::softwareVersion() {
    //软件版本
    QMessageBox::information(NULL,tr("软件版本" ),tr("风力发电机气动平衡检测系统 v2.0.0"));
}

void MainWindow::technicalSupport() {
    //技术支持
    QMessageBox::information(NULL,tr("技术支持"),tr("本软件由中国地质大学（北京）杜晋华开发"));
}

void MainWindow::updateLeftTop2() {
    leftTop->updateStaticChart();
}

void MainWindow::updateLeftDown2() {
    leftDown->updateStaticChart();
}

void MainWindow::paint_data_delta() {
    leftTop->paint_data_delta();
}

void MainWindow::on_mouseMovePoint(QPoint point)
{ //鼠标移动响应
    if(which == 0) {
        QPointF pt= this->leftTop->chart()->mapToValue(point); //转换为图表的数值
        labXYValue->setText(QString::asprintf("数据源=%d,X=%.2f,Y=%.2f",which+1,pt.x(),pt.y())); //状态栏显示
    } else {
        QPointF pt= this->leftDown->chart()->mapToValue(point); //转换为图表的数值
        labXYValue->setText(QString::asprintf("数据源=%d,X=%.2f,Y=%.2f",which+1,pt.x(),pt.y())); //状态栏显示
    }
}

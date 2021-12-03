#include <QGridLayout>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <fstream>
#include "global.h"
#include "pickwidget.h"
#include "righttopwidget.h"
using namespace std;
pickWidget::pickWidget(QWidget *parent) : QWidget(parent) {
    prighttop = (rightTopWidget *)parent;

    maxLabel = new QLabel(this);
    maxLabel->setText(tr("       最大值       "));
    minLabel = new QLabel(this);
    minLabel->setText(tr("       最小值       "));
    maxEdit = new QLineEdit("", this);
    minEdit = new QLineEdit("", this);
    pickButton = new QPushButton(tr("1.确定"), this);
    correctButton = new QPushButton(tr("2.纠错"), this);
    finddifferenceButton = new QPushButton(tr("3.求差值"), this);
    dataclassButton = new QPushButton(tr("  4.数据分类"), this);
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(minLabel, 0, 0);
    mainLayout->addWidget(minEdit, 0, 1);
    mainLayout->addWidget(maxLabel, 1, 0);
    mainLayout->addWidget(maxEdit, 1, 1);
    mainLayout->addWidget(pickButton, 2, 0);
    mainLayout->addWidget(correctButton, 2, 1);
    mainLayout->addWidget(finddifferenceButton, 3, 0);
    mainLayout->addWidget(dataclassButton, 3, 1);
    /*correctButton->hide();
    finddifferenceButton->hide();
    dataclassButton->hide();*/
    connect(pickButton, SIGNAL(clicked()), this, SLOT(sendInfo()));
    connect(correctButton, SIGNAL(clicked()), this, SLOT(sendInfo1()));
    connect(finddifferenceButton, SIGNAL(clicked()), this, SLOT(sendInfo2()));
    connect(dataclassButton, SIGNAL(clicked()), this, SLOT(sendInfo3()));
    setLayout(mainLayout);
}

//设置最大值和最小值，并调用pick函数完成最大值和最小值的筛选
void pickWidget::sendInfo() {
    double temp;
    bool ok;
    QString dialog;
    temp = minEdit->text().toDouble(&ok);

    if (ok == false) {
        dialog = "最小值设置无效\n";
        QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
        return;
    }
    dataLow = temp;
    temp = maxEdit->text().toDouble(&ok);

    if (ok == false) {
        dialog = "最大值设置无效\n";
        QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
        return;
    }
    dataHigh = temp;

    pick();
    //这里少一步容错机制
    dialog = "筛选设置成功\n";
    QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);

    /*
    //筛选之后图像应该发生变化
    if(which == 0) { //刷新上图
        prighttop->updateLeftTop();
    } else { //刷新下图
        prighttop->updateLeftDown();
    }
    */
}

void pickWidget::sendInfo1()
{
    //纠错
    correct();
    QString dialog;
    dialog = "纠错成功\n";
    //correctButton->hide();
    //finddifferenceButton->show();
    QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);

    /*
    //纠错之后图像应该发生变化
    if(which == 0) { //刷新上图
        prighttop->updateLeftTop();
    } else { //刷新下图
        prighttop->updateLeftDown();
    }
    */
}

void pickWidget::sendInfo2()
{
    //求差值
    finddifference();
    QString dialog;
    dialog = "计算成功\n";

    //加上画data_delta图
    //prighttop->paint_data_delta();
    //暂时禁止掉，画图速度太慢了。参照https://blog.csdn.net/duixiaoyan/article/details/88916956实现快速绘制

    QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
}
void pickWidget::sendInfo3()
{
    //数据分类
    dataclass();
    QString dialog;
    dialog = "成功\n";

    //画data_length图



    QMessageBox::information(this, "提示", dialog, QMessageBox::Ok);
}

void pickWidget:: pick(){
    //实现筛选功能
    //根据DATAHIGH和DATALOW进行精选
    //用户设置的最大值和最小值，需要设置进行相应的传入
    vector<double>::iterator itDouble;
    while(true){
        dataNum1.clear();
        itDouble = dataBucket1.begin();

        /*20211203
        for(; itDouble != dataBucket1.end();++itDouble){
            if(*itDouble > dataHigh || *itDouble < dataLow){
                dataNum1.push_back(1);
            }else{
                dataNum1.push_back(*itDouble);
            }
        }
        */

        for(; itDouble != dataBucket1.end();++itDouble){
            if(*itDouble > dataHigh){
                dataNum1.push_back(dataHigh);
            }else if(*itDouble < dataLow){
                dataNum1.push_back(dataLow);
            }else{
                dataNum1.push_back(*itDouble);
            }
        }
        break;
        /*
         * //去掉当前的最大值和最小值的东西，暂且不要！
        itDouble = dataNum1.begin();
        bool flag = 0;
        for(; itDouble != dataNum1.end();++itDouble){
            if(*itDouble != 1 && (*itDouble > DATAHIGH || *itDouble < DATALOW)){
                if(*itDouble > DATAHIGH)
                    QMessageBox::warning(NULL, tr("警告！"), tr("最大值设置太大"));
                else
                    QMessageBox::warning(NULL, tr("警告！"), tr("最小值设置太小"));
                flag = 1;
                break;
            }
        }
        if(flag) continue;
        //这里还应该有一步纠错
        break;
        */
    }
    return ;
/*
    纠错按钮的实际效果
    bool flag = 0;
    for(itDouble = dataNum1.begin();itDouble != dataNum1.end();++itDouble){
        if(*itDouble == 1){
            flag = 1;
            break;
        }
    }//找到第一个1

    if(flag){
        vector<double>::iterator itLast = itDouble;
        ++itDouble;
        for(;itDouble != dataNum1.end();++itDouble){
            if(*itDouble == 1){
                if(itDouble - itLast <= 20){
                    *itLast = dataLow;
                }else{
                    if(itLast != dataNum1.begin()){
                        *itLast = *(itLast - 1);
                    }else if(itLast != dataNum1.end()){
                        *itLast = *(itLast + 1);
                    }
                }
                itLast = itDouble;
            }
        }//找到相邻的1，进行相应的操作
        *itLast = *(itLast - 1);
    }

    达到效果：于dataNum1中存储了所有的，已经修改成功的数据，全部都是浮点型数据，均为传感器测得的距离
    数据的最终获取
    itDouble = dataNum1.begin();
    ++itDouble;
    for(;itDouble != dataNum1.end();++itDouble){
        dataDelta1.push_back(fabs(*itDouble - *(itDouble-1)));
    }//差值数组处理完毕

    //显示一下差值数组

    vector<double> temp;
    int size = dataDelta1.size();
    for(int i = 0;i < size;++i){
        if(dataDelta1[i] > threShold){
            temp.push_back(dataDelta1[i]);
        }
    }
    //得到temp数组，含义：差值数组中大于阈值的元素，及其下标

    itDouble = temp.begin();
    ++itDouble;
    for(;itDouble != temp.end();){
        if((*itDouble) - *(itDouble-1) < 25){
            temp.erase(itDouble);
        }else{
            ++itDouble;
        }
    }
//    for(itDouble = temp.begin();itDouble != temp.end();++itDouble) qDebug() << *itDouble;
    //改进算法，包括的步骤：对temp处理，后一个减前一个，另
//    存为数组b，b中小于25的向上寻找，找到temp中对应元素，并且删除

    double delta = dataHigh;
    for(itDouble = temp.begin();itDouble != temp.end();++itDouble){
        delta = min(delta,(*itDouble));
    }
    //获取temp中的最小值，delta，作为data_delta中的最小值
    vector<int> index;
    size = dataDelta1.size();
    for(int i = 0;i < size;++i){
        if(dataDelta1[i] >= delta){
            index.push_back(i);
        }
    }
    //获取dataDelta1中大于等于delta的所有元素位置
//    qDebug() << index.size();

    vector<int>::iterator itInt = index.begin();
    ++itInt;
    for(;itInt != index.end();){
        if(*itInt - *(itInt-1) < 25){
            index.erase(itInt);
        }else{
            ++itInt;
        }
    }
    //同上面的改进算法，将index中的前后差小于25的元素去除

//    for(itInt = index.begin();itInt != index.end();++itInt) qDebug() << *itInt;

    size = index.size();
    dataNumCell = new double*[size];
    for(int i = 1;i < size;++i){
        dataNumCell[i-1] = new double[index[i] - index[i-1]];//50-30 = 20
        dataLength.push_back(index[i] - index[i-1]);//20
        for(int j = index[i-1]+1,k = 0;j <= index[i];++j,++k){//循环20次，
            dataNumCell[i-1][k] = dataNum1[j];//正好对应[0,19]
        }
    }
    //处理dataNumCell，建立二维数组，一共是size-1个数组，[0,size-2]

    size = dataLength.size() / 6 * 6;//找到blade数组的最小行数，作为行数
    //例如现在index中size为59，则每一个blade数组的大小都是[0,9)
    blade1RootCell = new double*[size/6];//0
    blade1VibCell = new double*[size/6];//1
    blade2RootCell = new double*[size/6];//2
    blade2VibCell = new double*[size/6];//3
    blade3RootCell = new double*[size/6];//4
    blade3VibCell = new double*[size/6];//5

    int nTotal = 0;
    int n1,n2,n3;
    n1 = n2 = n3 = 0;
    //顺便求出来每一个齿间距
    for(int i = 0;i < size;++i){
        nTotal += dataLength[i];
        if(i % 6 == 0){
            blade1RootCell[i / 6] = new double[dataLength[i]];
            for(int j = 0;j < dataLength[i];++j){
                blade1RootCell[i / 6][j] = dataNumCell[i][j];
//                if(blade1RootCell[i / 6][j] > 80)
//                qDebug() << blade1RootCell[i / 6][j];
            }
            n1 += dataLength[i];
        }else if(i % 6 == 1){
            blade1VibCell[i / 6] = new double[dataLength[i]];
            for(int j = 0;j < dataLength[i];++j){
                blade1VibCell[i / 6][j] = dataNumCell[i][j];
            }
            n1 += dataLength[i];
        }else if(i % 6 == 2){
            blade2RootCell[i / 6] = new double[dataLength[i]];
            for(int j = 0;j < dataLength[i];++j){
                blade2RootCell[i / 6][j] = dataNumCell[i][j];
            }
            n2 += dataLength[i];
        }else if(i % 6 == 3){
            blade2VibCell[i / 6] = new double[dataLength[i]];
            for(int j = 0;j < dataLength[i];++j){
                blade2VibCell[i / 6][j] = dataNumCell[i][j];
            }
            n2 += dataLength[i];
        }else if(i % 6 == 4){
            blade3RootCell[i / 6] = new double[dataLength[i]];
            for(int j = 0;j < dataLength[i];++j){
                blade3RootCell[i / 6][j] = dataNumCell[i][j];
            }
            n3 += dataLength[i];
        }else if(i % 6 == 5){
            blade3VibCell[i / 6] = new double[dataLength[i]];
            for(int j = 0;j < dataLength[i];++j){
                blade3VibCell[i / 6][j] = dataNumCell[i][j];
            }
            n3 += dataLength[i];
        }
    }
    //对各个blade数组进行初步的赋值

    //求出各个叶片的齿间距，此处需要在对话框中进行显示
    teiLung1 = n1 * 360 / nTotal - 120;
    teiLung2 = n2 * 360 / nTotal - 120;
    teiLung3 = n3 * 360 / nTotal - 120;
//    qDebug() << teiLung1 << teiLung2 << teiLung3;

    double m[size/6];
    for(int i=0;i<size/6;++i)
    {
        m[i]=0;
        for(int j=0;j<6;++j)
        {
            m[i]+=dataLength[i*6+j];
        }
    }
    rpm=new double[size/6];//rpm[i]表示转第i+1圈时的平均转速（转/分钟）
    for(int i=0;i<size/6;++i)
    {
        rpm[i]=rootFrequency*60/m[i];
        //qDebug()<<"rpm[i]:"<<rpm[i];
    }
*/
    /*for(int i = 0;i < size / 6;++i){
        for(int j = 0;j < dataLength[i * 6];++j){
            qDebug() << blade1RootCell[i][j];
        }
    }*/

    /*for(int i=0;i<size;++i)
    {
        qDebug()<<dataLength[i];
    }*/
/*
    double cosanum=cos(aAngle*M_PI/180),cosbnum=cos(bAngle*M_PI/180);//根据输入的角度计算cos值
    //qDebug()<<"cosanum:"<<cosanum<<" cosbnum:"<<cosbnum;
    blade1_root_temp=new double*[size/6];
    blade2_root_temp=new double*[size/6];
    blade3_root_temp=new double*[size/6];//这三个数组将以上n*dataLength[i]的二维数组处理为n*3201的二维数组(空间平均铺取)
    blade1_root=new double[3201];
    blade2_root=new double[3201];
    blade3_root=new double[3201];//这三个数组将上面三个n*3201的二维数组处理为1*3201的一维数组(每列处理出一个具有代表性的数据)
    blade1_root_tem=new double[3201];
    blade2_root_tem=new double[3201];
    blade3_root_tem=new double[3201];//这三个数组是上面三个1*3201的一维数组进行拟合之后的结果
    blade_root_tem_ave=new double[3201];//将上面三个拟合之后的一维数组每列的数据取平均之后得到的一个1*3201的一维数组
    for(int i=0;i<size/6;++i)
    {
        blade1_root_temp[i]=new double[3201];
        blade2_root_temp[i]=new double[3201];
        blade3_root_temp[i]=new double[3201];
        double d1=3200.0/(dataLength[i*6]-1);
        double d2=3200.0/(dataLength[i*6+2]-1);
        double d3=3200.0/(dataLength[i*6+4]-1);
        //qDebug()<<"size1:"<<dataLength[i*6]<<" size2:"<<dataLength[i*6+2]<<" size3:"<<dataLength[i*6+4];
        //qDebug("%.2f %.2f %.2f",d1,d2,d3);
        for(int j=0;j<3201;++j)
        {
            //qDebug()<<"pos1:"<<round(j/d1)<<" pos2:"<<round(j/d1)<<" pos3:"<<round(j/d1);
            blade1_root_temp[i][j]=blade1RootCell[i][(int)round(j/d1)]*cosanum;
            blade2_root_temp[i][j]=blade2RootCell[i][(int)round(j/d2)]*cosanum;
            blade3_root_temp[i][j]=blade3RootCell[i][(int)round(j/d3)]*cosanum;
        }
    }

    //调用外部函数对列处理，每列处理出一个理想值
    long double sum1,sum2,sum3;
    for(int j=0;j<3201;++j)
    {
        sum1=0,sum2=0,sum3=0;
        for(int i=0;i<size/6;++i)
        {
            sum1+=blade1_root_temp[i][j];
            sum2+=blade2_root_temp[i][j];
            sum3+=blade3_root_temp[i][j];
            qDebug()<<blade1_root_temp[i][j];
        }
        blade1_root[j]=sum1/(size/6);
        blade2_root[j]=sum2/(size/6);
        blade3_root[j]=sum3/(size/6);
        //qDebug()<<j<<" "<<blade1_root[j];
    }

    //增加写文件的功能
    ofstream fout("D:\\blade1_root.txt");
    for(int i = 0;i < 3201;++i) fout << blade1_root[i] << endl;
    fout.close();
    fout.open("D:\\blade2_root.txt");
    for(int i = 0;i < 3201;++i) fout << blade2_root[i] << endl;
    fout.close();
    fout.open("D:\\blade3_root.txt");
    for(int i = 0;i < 3201;++i) fout << blade3_root[i] << endl;
    //再调用外部函数对行进行拟合

    for(int i=0;i<3200;++i)//由于没有得到每列选取具有代表性的数据以及拟合操作的函数,这里平均数数组的计算直接取二维数组的第一行元素进行
    {
        blade_root_tem_ave[i]=(blade1_root_temp[0][i]+blade2_root_temp[0][i]+blade3_root_temp[0][i])/3;
    }
*/
}

void pickWidget:: correct(){
    bool flag = false;
    vector<double>::iterator itDouble;
    for(itDouble = dataNum1.begin();itDouble != dataNum1.end();++itDouble){
        if(*itDouble == 1){
            flag = true;
            break;
        }
    }//找到第一个1

    if(flag == true){
        vector<double>::iterator itLast = itDouble;
        ++itDouble;
        for(;itDouble != dataNum1.end();++itDouble){
            if(*itDouble == 1){
                if(itDouble - itLast <= 20){
                    *itLast = dataLow;
                }else{
                    if(itLast != dataNum1.begin()){
                        *itLast = *(itLast - 1);
                    }else if(itLast != dataNum1.end()){
                        *itLast = *(itLast + 1);
                    }
                }
                itLast = itDouble;
            }
        }//找到相邻的1，进行相应的操作:相邻两个1的数据间距小于20，则替换为最小值，否则替换为近处的值
        *itLast = *(itLast - 1);
    }
}

void pickWidget:: finddifference(){
    //求差值：相邻两数据的差值的绝对值
    vector<double>::iterator itDouble;
    itDouble = dataNum1.begin();
    ++itDouble;
    for(;itDouble != dataNum1.end();++itDouble){
        dataDelta1.push_back(fabs(*itDouble - *(itDouble-1)));
    }//差值数组处理完毕
}


void pickWidget:: dataclass(){
   //std::vector<std::vector<double> > dataBucket11;
    vector<double>::iterator itDouble;
    itDouble = dataNum1.begin();
    bool flag = false;
    int index = 0;

    for(;itDouble != dataNum1.end();++itDouble){
        if(*itDouble < (dataHigh + dataLow) / 2.0) {
               if(flag == false) {
                   vector<double> tempv;
                   tempv.push_back(*itDouble);
                   dataBucket11.push_back(tempv);
                   flag = true;
                   ++index;
               } else {
                   dataBucket11[index - 1].push_back(*itDouble);
               }
        } else {
            flag = false;
        }

//    vector<double> temp;
//    vector<double>::iterator itDouble;
//    int size = dataDelta1.size();
//    for(int i = 0;i < size;++i){
//        if(dataDelta1[i] > threShold){
//            temp.push_back(dataDelta1[i]);
//        }
//    }
//    //得到temp数组，含义：差值数组中大于阈值的元素，及其下标

//    itDouble = temp.begin();
//    ++itDouble;
//    for(;itDouble != temp.end();){
//        if((*itDouble) - *(itDouble-1) < 25){ //25是自定义的一个值
//            temp.erase(itDouble);
//        }else{
//            ++itDouble;
//        }
//    }
////    for(itDouble = temp.begin();itDouble != temp.end();++itDouble) qDebug() << *itDouble;
//    //改进算法，包括的步骤：对temp处理，后一个减前一个，另
////    存为数组b，b中小于25的向上寻找，找到temp中对应元素，并且删除

//    double delta = dataHigh;
//    for(itDouble = temp.begin();itDouble != temp.end();++itDouble){
//        delta = min(delta,(*itDouble));
//    }
//    //获取temp中的最小值，delta，作为data_delta中的最小值
//    vector<int> index;
//    size = dataDelta1.size();
//    for(int i = 0;i < size;++i){
//        if(dataDelta1[i] >= delta){
//            index.push_back(i);
//        }
//    }
//    //获取dataDelta1中大于等于delta的所有元素位置
////    qDebug() << index.size();

//    vector<int>::iterator itInt = index.begin();
//    ++itInt;
//    for(;itInt != index.end();){
//        if(*itInt - *(itInt-1) < 25){
//            index.erase(itInt);
//        }else{
//            ++itInt;
//        }
//    }
//    //同上面的改进算法，将index中的前后差小于25的元素去除

////    for(itInt = index.begin();itInt != index.end();++itInt) qDebug() << *itInt;

//    size = index.size();
//    dataNumCell = new double*[size];
//    for(int i = 1;i < size;++i){
//        dataNumCell[i-1] = new double[index[i] - index[i-1]];//50-30 = 20
//        dataLength.push_back(index[i] - index[i-1]);//20
//        for(int j = index[i-1]+1,k = 0;j <= index[i];++j,++k){//循环20次，
//            dataNumCell[i-1][k] = dataNum1[j];//正好对应[0,19]
//        }
//    }
//    //处理dataNumCell，建立二维数组，一共是size-1个数组，[0,size-2]

//    size = dataLength.size() / 6 * 6;//找到blade数组的最小行数，作为行数
//    //例如现在index中size为59，则每一个blade数组的大小都是[0,9)
//    blade1RootCell = new double*[size/6];//0
//    blade1VibCell = new double*[size/6];//1
//    blade2RootCell = new double*[size/6];//2
//    blade2VibCell = new double*[size/6];//3
//    blade3RootCell = new double*[size/6];//4
//    blade3VibCell = new double*[size/6];//5

//    int nTotal = 0;
//    int n1,n2,n3;
//    n1 = n2 = n3 = 0;
//    //顺便求出来每一个齿间距
//    for(int i = 0;i < size;++i){
//        nTotal += dataLength[i];
//        if(i % 6 == 0){
//            blade1RootCell[i / 6] = new double[dataLength[i]];
//            for(int j = 0;j < dataLength[i];++j){
//                blade1RootCell[i / 6][j] = dataNumCell[i][j];
////                if(blade1RootCell[i / 6][j] > 80)
////                qDebug() << blade1RootCell[i / 6][j];
//            }
//            n1 += dataLength[i];
//        }else if(i % 6 == 1){
//            blade1VibCell[i / 6] = new double[dataLength[i]];
//            for(int j = 0;j < dataLength[i];++j){
//                blade1VibCell[i / 6][j] = dataNumCell[i][j];
//            }
//            n1 += dataLength[i];
//        }else if(i % 6 == 2){
//            blade2RootCell[i / 6] = new double[dataLength[i]];
//            for(int j = 0;j < dataLength[i];++j){
//                blade2RootCell[i / 6][j] = dataNumCell[i][j];
//            }
//            n2 += dataLength[i];
//        }else if(i % 6 == 3){
//            blade2VibCell[i / 6] = new double[dataLength[i]];
//            for(int j = 0;j < dataLength[i];++j){
//                blade2VibCell[i / 6][j] = dataNumCell[i][j];
//            }
//            n2 += dataLength[i];
//        }else if(i % 6 == 4){
//            blade3RootCell[i / 6] = new double[dataLength[i]];
//            for(int j = 0;j < dataLength[i];++j){
//                blade3RootCell[i / 6][j] = dataNumCell[i][j];
//            }
//            n3 += dataLength[i];
//        }else if(i % 6 == 5){
//            blade3VibCell[i / 6] = new double[dataLength[i]];
//            for(int j = 0;j < dataLength[i];++j){
//                blade3VibCell[i / 6][j] = dataNumCell[i][j];
//            }
//            n3 += dataLength[i];
//        }
//    }
//    //对各个blade数组进行初步的赋值

//    //求出各个叶片的齿间距，此处需要在对话框中进行显示
//    teiLung1 = n1 * 360 / nTotal - 120;
//    teiLung2 = n2 * 360 / nTotal - 120;
//    teiLung3 = n3 * 360 / nTotal - 120;
////    qDebug() << teiLung1 << teiLung2 << teiLung3;

//    double m[size/6];
//    for(int i=0;i<size/6;++i)
//    {
//        m[i]=0;
//        for(int j=0;j<6;++j)
//        {
//            m[i]+=dataLength[i*6+j];
//        }
//    }
//    rpm=new double[size/6];//rpm[i]表示转第i+1圈时的平均转速（转/分钟）
//    for(int i=0;i<size/6;++i)
//    {
//        rpm[i]=rootFrequency*60/m[i];
//        //qDebug()<<"rpm[i]:"<<rpm[i];
//    }

//    /*for(int i = 0;i < size / 6;++i){
//        for(int j = 0;j < dataLength[i * 6];++j){
//            qDebug() << blade1RootCell[i][j];
//        }
//    }*/

//    /*for(int i=0;i<size;++i)
//    {
//        qDebug()<<dataLength[i];
//    }*/

//    double cosanum=cos(aAngle*M_PI/180),cosbnum=cos(bAngle*M_PI/180);//根据输入的角度计算cos值
//    //qDebug()<<"cosanum:"<<cosanum<<" cosbnum:"<<cosbnum;
//    blade1_root_temp=new double*[size/6];
//    blade2_root_temp=new double*[size/6];
//    blade3_root_temp=new double*[size/6];//这三个数组将以上n*dataLength[i]的二维数组处理为n*3201的二维数组(空间平均铺取)
//    blade1_root=new double[3201];
//    blade2_root=new double[3201];
//    blade3_root=new double[3201];//这三个数组将上面三个n*3201的二维数组处理为1*3201的一维数组(每列处理出一个具有代表性的数据)
//    blade1_root_tem=new double[3201];
//    blade2_root_tem=new double[3201];
//    blade3_root_tem=new double[3201];//这三个数组是上面三个1*3201的一维数组进行拟合之后的结果
//    blade_root_tem_ave=new double[3201];//将上面三个拟合之后的一维数组每列的数据取平均之后得到的一个1*3201的一维数组
//    for(int i=0;i<size/6;++i)
//    {
//        blade1_root_temp[i]=new double[3201];
//        blade2_root_temp[i]=new double[3201];
//        blade3_root_temp[i]=new double[3201];
//        double d1=3200.0/(dataLength[i*6]-1);
//        double d2=3200.0/(dataLength[i*6+2]-1);
//        double d3=3200.0/(dataLength[i*6+4]-1);
//        //qDebug()<<"size1:"<<dataLength[i*6]<<" size2:"<<dataLength[i*6+2]<<" size3:"<<dataLength[i*6+4];
//        //qDebug("%.2f %.2f %.2f",d1,d2,d3);
//        for(int j=0;j<3201;++j)
//        {
//            //qDebug()<<"pos1:"<<round(j/d1)<<" pos2:"<<round(j/d1)<<" pos3:"<<round(j/d1);
//            blade1_root_temp[i][j]=blade1RootCell[i][(int)round(j/d1)]*cosanum;
//            blade2_root_temp[i][j]=blade2RootCell[i][(int)round(j/d2)]*cosanum;
//            blade3_root_temp[i][j]=blade3RootCell[i][(int)round(j/d3)]*cosanum;
//        }
    }

//    //调用外部函数对列处理，每列处理出一个理想值
//    long double sum1,sum2,sum3;
//    for(int j=0;j<3201;++j)
//    {
//        sum1=0,sum2=0,sum3=0;
//        for(int i=0;i<size/6;++i)
//        {
//            sum1+=blade1_root_temp[i][j];
//            sum2+=blade2_root_temp[i][j];
//            sum3+=blade3_root_temp[i][j];
////            qDebug()<<blade1_root_temp[i][j];
//        }
//        blade1_root[j]=sum1/(size/6);
//        blade2_root[j]=sum2/(size/6);
//        blade3_root[j]=sum3/(size/6);
//        //qDebug()<<j<<" "<<blade1_root[j];
//    }

//    //增加写文件的功能
//    ofstream fout("D:\\blade1_root.txt");
//    for(int i = 0;i < 3201;++i) fout << blade1_root[i] << endl;
//    fout.close();
//    fout.open("D:\\blade2_root.txt");
//    for(int i = 0;i < 3201;++i) fout << blade2_root[i] << endl;
//    fout.close();
//    fout.open("D:\\blade3_root.txt");
//    for(int i = 0;i < 3201;++i) fout << blade3_root[i] << endl;
//    //再调用外部函数对行进行拟合

//    for(int i=0;i<3200;++i)//由于没有得到每列选取具有代表性的数据以及拟合操作的函数,这里平均数数组的计算直接取二维数组的第一行元素进行
//    {
//        blade_root_tem_ave[i]=(blade1_root_temp[0][i]+blade2_root_temp[0][i]+blade3_root_temp[0][i])/3;
//    }
}

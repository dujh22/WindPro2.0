#include <string>
#include <vector>

/*所有参数的声明*/

std::vector<double> dataBucket1;
std::vector<std::vector<double> > dataBucket11;
std::vector<double> dataBucket2;
//默认data中存储的已经是全部数据，分三类，0,1，distance
//    std::vector<int> data
std::vector<int> timeStamp;
//存储对应位置的时间戳

/*传感器信息传参*/
/*风机信息传参,浮点数为-1或者字符串为空说明不需要更新*/
int rootFrequency = 2000;
int tipFrequency = 2000;

/*条件信息*/
std::string itemName = "";
std::string dataName = "";
double beginTime = -1;
double endTime = -1;

/*显示信息*/
int which = 0; //表明当前处理哪张图像0-上 1-下
int beginPos = 0; //起始坐标
int endPos = 10000; //终止坐标
int Delta = 50;   //间隔

/*数据信息*/
double aAngle = 60;
double bAngle = 30;

double DATAHIGH = 150;//默认存储的最大值
double DATALOW = 60;//默认存储的最小值
double dataHigh = DATAHIGH;//用户传入的最大值
double dataLow = DATALOW; //用户传入的最小值
std::vector<double> dataNum1;
std::vector<double> dataDelta1;
std::vector<int> dataLength;//存储每一个dataNumCell中一维数组的长度
double **dataNumCell;
double threShold = 1;//阈值
double **blade1RootCell;//叶片1
double **blade2RootCell;//叶片2
double **blade3RootCell;//叶片3
double **blade1VibCell;//非叶片1
double **blade2VibCell;//非叶片2
double **blade3VibCell;//非叶片3
double teiLung1,teiLung2,teiLung3;//与预期齿间距的差值
double *rpm;//转速数组
double **blade1_root_temp;//处理过的叶片1
double **blade2_root_temp;//处理过的叶片2
double **blade3_root_temp;//处理过的叶片3
double *blade1_root;//将上面的3200*n的数组处理为3200*1之后得到的数组
double *blade2_root;//每一个叶片，若干个周期中导出一个理想值，提取为一维数组
double *blade3_root;
double *blade1_root_tem;//将上面的3200*1的数组处理后的数组进行拟合后得到的数组
double *blade2_root_tem;
double *blade3_root_tem;
double *blade_root_tem_ave;//将上面三个3200*1的拟合后的数组求平均数之后得到的3200*1的数组


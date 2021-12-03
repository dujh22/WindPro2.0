#include <string>
#include <vector>

/*风机信息传参,浮点数为-1或者字符串为空说明不需要更新*/
int rootFrequency = 2000, tipFrequency = 2000;
/*条件信息*/
std::string itemName = "", dataName = "";
double beginTime = -1, endTime = -1;
/*数据信息*/
double aAngle = 60, bAngle = 30;

std::vector<double> dataBucket;
//默认data中存储的已经是全部数据，分三类，0,1，distance
//    std::vector<int> data
std::vector<int> timeStamp;
//存储对应位置的时间戳
double DATAHIGH = 150;//默认存储的最大值
double DATALOW = 60;//默认存储的最小值
double dataHigh = DATAHIGH,dataLow = DATALOW;//用户传入的最大值和最小值
std::vector<double> dataNum1;
std::vector<double> dataDelta1;
double** dataNumCell;
std::vector<int> dataLength;//存储每一个dataNumCell中一维数组的长度
double threShold = 1;//阈值
double **blade1RootCell;//叶片1
double **blade2RootCell;//叶片2
double **blade3RootCell;//叶片3
double **blade1VibCell;//非叶片1
double **blade2VibCell;//非叶片2
double **blade3VibCell;//非叶片3
double teiLung1,teiLung2,teiLung3;//齿间距
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


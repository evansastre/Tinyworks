#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <cctype>
#include <QtGui>
#include <QDialog>
#include <QLabel>

#include <QVector>

using namespace std;
namespace Ui
{
    class Widget;
}

class Widget : public QDialog {

    Q_OBJECT
public:

    Widget( QWidget *parent=0);
    ~Widget();

    int movecondition,NoDisk,BadInput,Victor, Continue;//判定错误与状态：状态，取的杆不存在塔层，放置杆的顶层小于取的层，胜利，继续
    int movestimes;//移动计数
    int pegs;//存储层数

    int disknum,lefrom, leto;//初始层数，取的塔，放的塔
    int lastdisk;//用于记录上一次开始时设定层数，以删除显示塔层

    vector<int>atop;//当前杆上各元素值
    vector < QStack<int> > poles;//将每个杆上堆叠的塔组合作为向量中元素，放在poles中
    QStack<int> stacks; //杆上的塔层

    int getlength(int i);//得到当前杆塔层个数
    int getpeg(vector< QStack<int> > &poles, int pegs);//取塔层
    int putpeg(vector< QStack<int> > &poles, int pegs);//放塔层

    bool Isdisknumchanged,Isbegun,isGetdisk;//是否改变层数设定（未改则载入默认数值），是否开始过初始化（未开始则给出错误提示，并返回）
    bool isCurrntChaged,Isbegunbefore;//是否取得盘;   在初始化时，判断是否设定过塔层，来确认是否执行清空塔层的命令
    bool timerstart;

    QImage Imagex[4];//存储图片，方便调用
    QPixmap  diskshow;//塔层的原图

    QColor colorasd[9];

    QLabel *Peg[3][9];

    void move();

    QTime zero,now,zz ;
    QTimer *timer;
    QTimer *dclock;



protected:
    void changeEvent(QEvent *e);
    void setpeg(int disks);//初始化
    void Init();//清空数据并使显示初始化（用于重新开始游戏时）

private:
    Ui::Widget *ui;
public slots:
    bool eventFilter(QObject*,QEvent*);

    void xytimerUpDate();//计时器显示的实现
    void dclockshow();


private slots:

    void on_pause_clicked();//计时器暂停与继续
    void on_spinBox_valueChanged(int );     //获取初始塔层数
    void on_exit_clicked();                 //退出
    void on_start_clicked();                //开始并初始化
    void on_Illustration_clicked();         //弹出说明


};

#endif


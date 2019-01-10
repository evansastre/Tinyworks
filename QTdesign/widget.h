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

    int movecondition,NoDisk,BadInput,Victor, Continue;//�ж�������״̬��״̬��ȡ�ĸ˲��������㣬���ø˵Ķ���С��ȡ�Ĳ㣬ʤ��������
    int movestimes;//�ƶ�����
    int pegs;//�洢����

    int disknum,lefrom, leto;//��ʼ������ȡ�������ŵ���
    int lastdisk;//���ڼ�¼��һ�ο�ʼʱ�趨��������ɾ����ʾ����

    vector<int>atop;//��ǰ���ϸ�Ԫ��ֵ
    vector < QStack<int> > poles;//��ÿ�����϶ѵ����������Ϊ������Ԫ�أ�����poles��
    QStack<int> stacks; //���ϵ�����

    int getlength(int i);//�õ���ǰ���������
    int getpeg(vector< QStack<int> > &poles, int pegs);//ȡ����
    int putpeg(vector< QStack<int> > &poles, int pegs);//������

    bool Isdisknumchanged,Isbegun,isGetdisk;//�Ƿ�ı�����趨��δ��������Ĭ����ֵ�����Ƿ�ʼ����ʼ����δ��ʼ�����������ʾ�������أ�
    bool isCurrntChaged,Isbegunbefore;//�Ƿ�ȡ����;   �ڳ�ʼ��ʱ���ж��Ƿ��趨�����㣬��ȷ���Ƿ�ִ��������������
    bool timerstart;

    QImage Imagex[4];//�洢ͼƬ���������
    QPixmap  diskshow;//�����ԭͼ

    QColor colorasd[9];

    QLabel *Peg[3][9];

    void move();

    QTime zero,now,zz ;
    QTimer *timer;
    QTimer *dclock;



protected:
    void changeEvent(QEvent *e);
    void setpeg(int disks);//��ʼ��
    void Init();//������ݲ�ʹ��ʾ��ʼ�����������¿�ʼ��Ϸʱ��

private:
    Ui::Widget *ui;
public slots:
    bool eventFilter(QObject*,QEvent*);

    void xytimerUpDate();//��ʱ����ʾ��ʵ��
    void dclockshow();


private slots:

    void on_pause_clicked();//��ʱ����ͣ�����
    void on_spinBox_valueChanged(int );     //��ȡ��ʼ������
    void on_exit_clicked();                 //�˳�
    void on_start_clicked();                //��ʼ����ʼ��
    void on_Illustration_clicked();         //����˵��


};

#endif


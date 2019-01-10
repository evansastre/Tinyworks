#include "widget.h"
#include "ui_widget.h"
#include <qmessagebox.h>
#include <cctype>
#include <QStack>
#include <qstring.h>
#include <QLayout>
#include <QtGui>
#include <QLabel>
#include <cmath>
using namespace std;


Widget::Widget( QWidget *parent )
            : QDialog( parent ),
 ui(new Ui::Widget)
{
    Isbegunbefore=false;
    Isbegun=false;

    ui->setupUi(this);
    ui->spinBox->selectAll();
    ui->spinBox->setFocus();//����������ʱ��λ���趨��������

    Imagex[0].load(":/new/prefix2/Image/ss.gif");//�����õ���һ����̬���ӿ��ļ�qgif4.dll����������ͼƬ�����ļ�����ʶ��gifͼ;��ͼ·��������qrc��
    Imagex[1].load(":/new/prefix2/Image/s1.jpg");
    Imagex[2].load(":/new/prefix2/Image/s2.jpg");
    Imagex[3].load(":/new/prefix2/Image/s3.jpg");
    diskshow.load(":/new/prefix2/Image/disk.png");
    colorasd[0]=(Qt::white);
    colorasd[1]=(Qt::darkBlue);
    colorasd[2]=(Qt::darkGreen);
    colorasd[3]=(Qt::darkMagenta);
    colorasd[4]=(Qt::darkGray);
    colorasd[5]=(Qt::blue);
    colorasd[6]=(Qt::green);
    colorasd[7]=(Qt::yellow);
    colorasd[8]=(Qt::cyan);


    ui->v1->installEventFilter(this);//�������¼�������
    ui->v2->installEventFilter(this);
    ui->v3->installEventFilter(this);

    ui->Label1->installEventFilter(this);//ͼ�ΰ�ť�����¼�������
    ui->Label2->installEventFilter(this);//ͼ�ΰ�ť�����¼�������
    ui->Label3->installEventFilter(this);//ͼ�ΰ�ť�����¼�������



    QDateTime nowtime = QDateTime::currentDateTime();//��ȡϵͳ���ڵ�ʱ��
    QString clock = nowtime.toString("yyyy-MM-dd hh:mm:ss");//����ϵͳʱ����ʾ��ʽ
    ui->clock->setText(clock);//�ڱ�ǩ����ʾʱ��

    dclock = new QTimer(this);   //�½���ʱ��
    connect(dclock,SIGNAL(timeout()),this,SLOT(dclockshow()));//������ʱ�������źź���Ӧ�Ĳۺ���
    dclock->start(1000);//��ʱ����ʼ��ʱ������1000��ʾ1000ms��1��
    //dclock->~QTimer();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Widget::on_Illustration_clicked()//����˵��
{
     QMessageBox::information(0, tr("��Ϸ˵��"),tr("��Ϸ��Ŀ���ǰ����е�����ӵ�һ���ƶ�����һ��.���������1��8������,�����ʼ��ť����ʼ��Ϸ. ͨ�������������λ�û��߶�ӦͼƬλ�û�ȡ�ͷ������㡣һ��ֻ���ƶ�һ�����㣬����ȡ�ͷŶ��Ƕ������㣬������㲻�ܷ�����С������֮�ϣ��������㰴��ʼ������������һ��ʱΪʤ�� "));
}

void Widget::on_spinBox_valueChanged(int z )//ͨ��spinbox���趨����
{
        disknum=z;
        Isdisknumchanged=true;//�����趨ֵ�Ѹ�
        ui->start->setFocus();
}

void Widget::on_start_clicked()// �����ʼ��ť
{

    if(Isbegun&&!timerstart)
    {
        QMessageBox::information(0, tr("��ʾ"),tr("��Ϸ��ͣ�У����ȵ���������ٽ������¿�ʼ��Ϸ"));//��Ϸ��ͣ�е����ʼ����������
        return;
    }
    if(!Isdisknumchanged)
    {
        disknum=1;
    };
    setpeg(disknum);
}

void Widget::on_exit_clicked()//�˳�
{
    close();
}

void Widget::setpeg(int disks)// ��һ�˳�ʼ��
{
    if(Isbegun)
    {
        timer->~QTimer();
    }

    NoDisk=1,Victor=2, BadInput=3,Continue=4;
    movecondition=Continue;
    movestimes=0;
    pegs=disks;
    lefrom=0,leto=0;
    Isbegun=true;
    isGetdisk=false;
    timerstart=true;


    //��ʱ��

    zz=zero=now = QTime::fromString("00:00:00","hh:mm:ss");

    int ctime=(pow(2,pegs)-1)*7;

    zero=zero.addSecs(ctime);
    now=zero;
    QString ste = zero.toString("hh:mm:ss");//����ϵͳʱ����ʾ��ʽ

    ui->lcdNumber->display(ste);//��lcdNumber����ʾʱ��
    timer = new QTimer(this);   //�½���ʱ��
    connect(timer,SIGNAL(timeout()),this,SLOT(xytimerUpDate()));//������ʱ�������źź���Ӧ�Ĳۺ���
    timer->start(1000);//��ʱ����ʼ��ʱ������1000��ʾ1000ms��1��


    for(int i=0;i<5;i++)
    {
        poles.push_back(stacks);//����5����,ǰ����Ϊ��Ϸ�ˣ����ġ�����Ϊ��ʱ�洢���ݵĸ�
    }

    if(Isbegunbefore)
    {
        Init() ;//��ʾ���
    }


    for(int i=pegs;i>=1;i--)
    {
        poles[0].push(i);//�Ե�һ�����ݳ�ʼ��
    }


    for( int i=1;i<=pegs;i++)// ��ʾ��һ�˳�ʼ����
    {
        //pixmap_2->fill( black );

        Peg[0][i]=new QLabel;
        QMatrix martix;
        martix.scale(0.5+0.3*i,1);
        QPixmap tmp=diskshow.transformed(martix);
        tmp.fill(colorasd[i]);
        Peg[0][i]->setAlignment(Qt::AlignHCenter);
        Peg[0][i]->setPixmap (tmp);
        ui->vl->addWidget(Peg[0][i]);
        tmp.fill(colorasd[0]);

        Peg[1][i]=new QLabel;
        Peg[1][i]->setPixmap (QPixmap::fromImage(Imagex[0]));
        ui->vm->addWidget(Peg[1][i]);

        Peg[2][i]=new QLabel;
        Peg[2][i]->setPixmap (QPixmap::fromImage(Imagex[0]));
        ui->vr->addWidget(Peg[2][i]);

    }

    Isbegunbefore=true;//���趨����ʼ����
    lastdisk=pegs;//��������������ϴ�����

}

void Widget::Init()
{
    for(int i=0;i<5;i++)
    {
         poles[i].clear();
    }

    for(int j=0;j<3;j++)
    {
        for(int i=1;i<=lastdisk;i++)//ɾ����ʾ������
        {
            delete Peg[j][i];
        }
    }

}



void Widget::move()//�ƶ������ʵ��
{
    if(movecondition!=Victor)//���״̬��ʤ������ִ���ƶ��ĺ���
    {
        if(isGetdisk)
        {
            movecondition=getpeg(poles, pegs);//ȡ����
        }

        else
        {
            movecondition=putpeg(poles, pegs);//������
        }

    }

    if(movecondition==NoDisk)
    {
        QMessageBox::information(0, tr("��ʾ"),tr("��ȡ������Ϊ��"));
        ui->Label1->setPixmap (QPixmap::fromImage(Imagex[1]));
        ui->Label2->setPixmap (QPixmap::fromImage(Imagex[2]));
        ui->Label3->setPixmap (QPixmap::fromImage(Imagex[3]));

        isGetdisk=false;
        ui->LabelState->setText(tr("��ѡȡ����"));
    }

    else if(movecondition==BadInput)
    {
        QMessageBox::information(0, tr("��ʾ"),tr("����������С�����������ǲ��������"));

        isGetdisk=true;
        ui->LabelState->setText(tr("���������"));

    }

    else if(movecondition==Victor)//ʤ����������ƶ���������ѡ��������Ϸ���˳�
    {
        movecondition=Continue;
        timer->stop ();

        const int timepast=now.secsTo(zero);

        QString ptimepast="";


        if(timepast/3600>0)
        {
            int hour=timepast/3600;
            ptimepast+=QString::number(hour);
            ptimepast+= tr("Сʱ ");
        }

        if((timepast%3600)/60>0)
        {
            int minute=(timepast%3600)/60;
            ptimepast+=QString::number(minute);
            ptimepast+= tr("���� ");
        }


        if(((timepast%3600)%60)>0)
        {
            int second=(timepast%3600)%60;
            ptimepast+=QString::number(second);
            ptimepast+= tr("�� ");
        }

        switch ( QMessageBox::warning( this,  tr("��ϲ"),
                                              tr("������")  + QString::number(movestimes) + tr("�������������Ϸ\n��ʱ")
                                              +QString::number(zz.secsTo(zero))+tr("��         ��ʱ")+ptimepast,
                                              tr("����һ��"), tr("�趨�µ����������¿�ʼ"),
                                              tr("�˳�"), 0, 2 ) )
           {
           case 0: //�û�����Play again��ť,���˻س���

               on_start_clicked();//�Ե�ǰ�趨�Ĳ������¿�ʼ��Ϸ
               break;
           case 1:
               Init();//ֻ����գ����û������µĲ���
               Isbegun=false;
               Isbegunbefore=false;
               timer->~QTimer();
               ui->spinBox->selectAll();
               ui->spinBox->setFocus();
               break;
           default:// �û�����Quit��ť,����Esc��
               close();
               break;
           }
    }

}

int Widget::getlength(int i)//�õ���ǰ���������
{
    int k;
    int length=0;


    while (!poles[i].empty()) //�����ǰ��������� ����ʱȡ����ǰ�������� ��
     {

         k=poles[i].top();
         atop.push_back(k);   //

         poles[3].push(poles[i].top());
         poles[i].pop();
         length++;
     };

      while (!poles[3].empty())//�Ż�����
      {
            poles[i].push(poles[3].top());// �ƶ�����ȡ��fromֵ��to��ֵ
            poles[3].pop();
      };
      return length;
}

int Widget::getpeg(vector< QStack<int> > &poles, int pegs)//ȡ����
{

       //�жϿ��ܳ��ֵĴ���ץȡ���̲���
        if(poles[lefrom-1].empty())//ץȡ���̲�����
        {
            return (NoDisk);
        }

       //�޴�����ִ��
        else
        {
            //����
            poles[4].push(poles[lefrom-1].top());
            poles[lefrom-1].pop();

             //������ʾ
            int n=getlength(lefrom-1);
            int m=pegs;

            for(int i=1;i<=pegs;i++)//ɾ����ǰ����ʾ������
            {
                delete Peg[lefrom-1][i] ;
            }

            for(int i=1;i<=(m-n);i++)//��λ��ʾ
            {
                Peg[lefrom-1][i]=new QLabel;

                if(lefrom==1)
                    ui->vl->addWidget(Peg[lefrom-1][i]);
                if(lefrom==2)
                    ui->vm->addWidget(Peg[lefrom-1][i]);
                if(lefrom==3)
                    ui->vr->addWidget(Peg[lefrom-1][i]);
            }

            for(int i=1;i<=n;i++)//��ǰ������������ʾ
            {
                Peg[lefrom-1][i]=new QLabel;

                QMatrix martix;
                martix.scale(0.5+0.3*atop[i-1],1);
                QPixmap tmp=diskshow.transformed(martix);
                tmp.fill(colorasd[atop[i-1]]);
                Peg[lefrom-1][i]->setAlignment(Qt::AlignHCenter);
                Peg[lefrom-1][i]->setPixmap (tmp);


                if(lefrom==1)
                    ui->vl->addWidget(Peg[lefrom-1][i]);
                if(lefrom==2)
                    ui->vm->addWidget(Peg[lefrom-1][i]);
                if(lefrom==3)
                    ui->vr->addWidget(Peg[lefrom-1][i]);
            }
            atop.clear();

        }

         return(Continue);
}


int Widget::putpeg(vector< QStack<int> > &poles, int pegs)//������
{
    //�жϿ��ܳ��ֵĴ��󣺷��ò��Ϲ���
    if(!poles[leto-1].empty() && poles[leto-1].top()<poles[4].top())//�ͷ�λ��Υ������
    {
         return (BadInput);
    }

    else if(poles[leto-1].empty() || poles[leto-1].top()>poles[4].top())
    {
        poles[leto-1].push(poles[4].top());// �ƶ�����ȡ���ݴ�ֵ��to��ֵ
        poles[4].pop();// ����ݴ��ֵ

       //������ʾ

        int a=getlength(leto-1);
        int b=pegs;


        for(int i=1;i<=b;i++)//ɾ����ǰ����ʾ������
        {
            delete Peg[leto-1][i] ;
        }


        for(int i=1;i<=(b-a);i++)//��λ����ʾ
        {
            Peg[leto-1][i]=new QLabel;

            if(leto==1)
                ui->vl->addWidget(Peg[leto-1][i]);
            if(leto==2)
                ui->vm->addWidget(Peg[leto-1][i]);
            if(leto==3)
                ui->vr->addWidget(Peg[leto-1][i]);
        }


        for(int i=1;i<=a;i++)  //��ǰ������������ʾ
        {
            Peg[leto-1][i]=new QLabel;

            QMatrix martix;
            martix.scale(0.5+0.3*atop[i-1],1);
            QPixmap tmp=diskshow.transformed(martix);
            tmp.fill(colorasd[atop[i-1]]);
            Peg[leto-1][i]->setAlignment(Qt::AlignHCenter);
            Peg[leto-1][i]->setPixmap (tmp);

            if(leto==1)
                ui->vl->addWidget(Peg[leto-1][i]);
            if(leto==2)
                ui->vm->addWidget(Peg[leto-1][i]);
            if(leto==3)
                ui->vr->addWidget(Peg[leto-1][i]);
        }
        atop.clear();

    }

     movestimes++;
     ui->Label1->setPixmap (QPixmap::fromImage(Imagex[1]));
     ui->Label2->setPixmap (QPixmap::fromImage(Imagex[2]));
     ui->Label3->setPixmap (QPixmap::fromImage(Imagex[3]));


    //�ж��ƶ����״̬��ʤ�����߼���
    if((leto-1)>0 &&( poles[leto-1].size())==pegs)
    {
        return(Victor);
    }

    else
    {
        return(Continue);
    }

}

bool Widget::eventFilter(QObject* watched,QEvent* event)
{

    if(watched ==ui->Label1 || watched == ui->v1 )   //��������ڵ�λ�û��߶�ӦͼƬλ��
    {
        if(event->type() == QEvent::MouseButtonPress)
        {

                QMouseEvent *mouseEvent = (QMouseEvent *)event;
                if(mouseEvent->buttons() &Qt::LeftButton)
                {
                    if(!Isbegun)//�ж���Ϸ�Ƿ����趨��ʼ����
                    {
                        QMessageBox::information(0, tr("��ʾ"),tr("�������ú�ŵ������"));//��δ��ʼ����������
                        ui->spinBox->selectAll();
                        ui->spinBox->setFocus();
                        return QDialog::eventFilter(watched,event);
                    }
                    if(!timerstart)
                    {
                         QMessageBox::information(0, tr("��ʾ"),tr("��Ϸ��ͣ�У�����������ť"));//
                         return QDialog::eventFilter(watched,event);
                    }

                    if(!isGetdisk)
                    {
                        ui->LabelState->setText(tr("���ȡ�˵�һ�˵Ķ�����"));
                        isGetdisk=true;
                        lefrom=1;

                        QMatrix martix;
                        martix.scale(0.8,0.8);
                        QImage tmp=Imagex[1].transformed(martix);
                        ui->Label1->setPixmap (QPixmap::fromImage(tmp));

                        move();
                    }

                    else
                    {
                        ui->LabelState->setText(tr("����������˵�һ�˵Ķ��� "));
                        isGetdisk=false;
                        leto=1;
                        move();
                    }

                }

                else if(mouseEvent->buttons() &Qt::RightButton)
                {
                        ui->LabelState->setText(tr("���ǵ�һ��"));
                }

        }


    }


    if(watched ==ui->Label2 || watched == ui->v2)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {

                QMouseEvent *mouseEvent = (QMouseEvent *)event;
                if(mouseEvent->buttons() &Qt::LeftButton)
                {
                    if(!Isbegun)
                    {
                        QMessageBox::information(0, tr("��ʾ"),tr("�������ú�ŵ������"));//��δ��ʼ����������
                        ui->spinBox->selectAll();
                        ui->spinBox->setFocus();
                        return QDialog::eventFilter(watched,event);
                    }

                    if(!timerstart)
                    {
                         QMessageBox::information(0, tr("��ʾ"),tr("��Ϸ��ͣ�У�����������ť"));//
                         return QDialog::eventFilter(watched,event);
                    }

                    if(!isGetdisk)
                    {
                        ui->LabelState->setText(tr("���ȡ�˵ڶ��˵Ķ�����"));
                        isGetdisk=true;
                        lefrom=2;

                        QMatrix martix;
                        martix.scale(0.8,0.8);
                        QImage tmp=Imagex[2].transformed(martix);
                        ui->Label2->setPixmap (QPixmap::fromImage(tmp));

                        move();
                    }

                    else
                    {
                        ui->LabelState->setText(tr("����������˵ڶ��˵Ķ��� "));
                        isGetdisk=false;
                        leto=2;
                        move();
                    }

                }

                else if(mouseEvent->buttons() &Qt::RightButton)
                {
                        ui->LabelState->setText(tr("���ǵڶ���"));
                }
        }

    }

    if(watched ==ui->Label3 || watched == ui->v3)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {

                QMouseEvent *mouseEvent = (QMouseEvent *)event;
                if(mouseEvent->buttons() &Qt::LeftButton)
                {
                    if(!Isbegun)
                    {
                        QMessageBox::information(0, tr("��ʾ"),tr("�������ú�ŵ������"));//��δ��ʼ����������
                        ui->spinBox->selectAll();
                        ui->spinBox->setFocus();
                        return QDialog::eventFilter(watched,event);
                    }

                    if(!timerstart)
                    {
                         QMessageBox::information(0, tr("��ʾ"),tr("��Ϸ��ͣ�У�����������ť"));//
                         return QDialog::eventFilter(watched,event);
                    }

                    if(!isGetdisk)
                    {
                        ui->LabelState->setText(tr("���ȡ�˵����˵Ķ����� "));
                        isGetdisk=true;
                        lefrom=3;

                        QMatrix martix;
                        martix.scale(0.8,0.8);
                        QImage tmp=Imagex[3].transformed(martix);
                        ui->Label3->setPixmap (QPixmap::fromImage(tmp));

                        move();
                    }

                    else
                    {
                        ui->LabelState->setText(tr("����������˵����˵Ķ��� "));
                        isGetdisk=false;
                        leto=3;
                        move();
                    }

                }

                else if(mouseEvent->buttons() &Qt::RightButton)
                {
                        ui->LabelState->setText(tr("���ǵ�����"));
                }
        }

    }
        return QDialog::eventFilter(watched,event);
}



void Widget::xytimerUpDate()
{
    if(zz==now)
    {
        movecondition=Continue;
        timer->stop ();
        QMessageBox::information(0, tr("��ʾ"),tr("ʱ�䵽����Ϸ�����¿�ʼ"));//
        on_start_clicked();//�Ե�ǰ�趨�Ĳ������¿�ʼ��Ϸ
        return;
    }
    now=now.addSecs (-1);
    QString strTime = now.toString("hh:mm:ss");//����ϵͳʱ����ʾ��ʽ
    ui->lcdNumber->display(strTime);//��lcdNumber����ʾʱ��
}

void Widget::dclockshow()
{
    QDateTime nowtime = QDateTime::currentDateTime();//��ȡϵͳ���ڵ�ʱ��
    QString clock = nowtime.toString("yyyy-MM-dd hh:mm:ss");//����ϵͳʱ����ʾ��ʽ
    ui->clock->setText(clock);//�ڱ�ǩ����ʾʱ��
}




void Widget::on_pause_clicked()
{

    if(!Isbegun)
    {
        QMessageBox::information(0, tr("��ʾ"),tr("���ȿ�ʼ��Ϸ"));//��δ��ʼ��������
        return ;
    }

    if(timerstart)
    {
        timer->stop ();
        ui->pause->setText(tr("����"));
        timerstart=false;

        for(int j=0;j<3;j++)
        {
            for(int i=1;i<=lastdisk;i++)//ɾ����ʾ������
            {
                Peg[j][i]->hide();
            }
        }

        Peg[0][0]=new QLabel;
        Peg[0][0]->setPixmap (QPixmap::fromImage(Imagex[0]));
        ui->vl->addWidget(Peg[0][0]);

        Peg[1][0]=new QLabel;
        Peg[1][0]->setPixmap (QPixmap::fromImage(Imagex[0]));
        ui->vm->addWidget(Peg[1][0]);

        Peg[2][0]=new QLabel;
        Peg[2][0]->setPixmap (QPixmap::fromImage(Imagex[0]));
        ui->vr->addWidget(Peg[2][0]);

    }

    else
    {
        timer->start ();
        ui->pause->setText(tr("��ͣ"));
        timerstart=true;
        for(int j=0;j<3;j++)
        {
            delete Peg[j][0];
        }

        for(int j=0;j<3;j++)
        {
            for(int i=1;i<=lastdisk;i++)//ɾ����ʾ������
            {
                Peg[j][i]->show();
            }
        }
    }

}

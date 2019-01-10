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
    ui->spinBox->setFocus();//开启主界面时定位在设定塔层数处

    Imagex[0].load(":/new/prefix2/Image/ss.gif");//这里用到了一个动态链接库文件qgif4.dll，拷贝至了图片所在文件夹以识别gif图;此图路径定义在qrc中
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


    ui->v1->installEventFilter(this);//杆载入事件过滤器
    ui->v2->installEventFilter(this);
    ui->v3->installEventFilter(this);

    ui->Label1->installEventFilter(this);//图形按钮载入事件过滤器
    ui->Label2->installEventFilter(this);//图形按钮载入事件过滤器
    ui->Label3->installEventFilter(this);//图形按钮载入事件过滤器



    QDateTime nowtime = QDateTime::currentDateTime();//获取系统现在的时间
    QString clock = nowtime.toString("yyyy-MM-dd hh:mm:ss");//设置系统时间显示格式
    ui->clock->setText(clock);//在标签上显示时间

    dclock = new QTimer(this);   //新建定时器
    connect(dclock,SIGNAL(timeout()),this,SLOT(dclockshow()));//关联定时器计满信号和相应的槽函数
    dclock->start(1000);//定时器开始计时，其中1000表示1000ms即1秒
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

void Widget::on_Illustration_clicked()//弹出说明
{
     QMessageBox::information(0, tr("游戏说明"),tr("游戏的目的是把所有的塔层从第一杆移动到另一杆.你可以设置1至8个塔层,点击开始按钮来开始游戏. 通过点击塔层所在位置或者对应图片位置获取和放置塔层。一次只能移动一个塔层，而且取和放都是顶端塔层，大的塔层不能放置在小的塔层之上，所有塔层按初始次序排列在另一杆时为胜利 "));
}

void Widget::on_spinBox_valueChanged(int z )//通过spinbox来设定层数
{
        disknum=z;
        Isdisknumchanged=true;//层数设定值已改
        ui->start->setFocus();
}

void Widget::on_start_clicked()// 点击开始按钮
{

    if(Isbegun&&!timerstart)
    {
        QMessageBox::information(0, tr("提示"),tr("游戏暂停中，请先点击继续，再进行重新开始游戏"));//游戏暂停中点击开始，弹出警告
        return;
    }
    if(!Isdisknumchanged)
    {
        disknum=1;
    };
    setpeg(disknum);
}

void Widget::on_exit_clicked()//退出
{
    close();
}

void Widget::setpeg(int disks)// 第一杆初始化
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


    //计时器

    zz=zero=now = QTime::fromString("00:00:00","hh:mm:ss");

    int ctime=(pow(2,pegs)-1)*7;

    zero=zero.addSecs(ctime);
    now=zero;
    QString ste = zero.toString("hh:mm:ss");//设置系统时间显示格式

    ui->lcdNumber->display(ste);//在lcdNumber上显示时间
    timer = new QTimer(this);   //新建定时器
    connect(timer,SIGNAL(timeout()),this,SLOT(xytimerUpDate()));//关联定时器计满信号和相应的槽函数
    timer->start(1000);//定时器开始计时，其中1000表示1000ms即1秒


    for(int i=0;i<5;i++)
    {
        poles.push_back(stacks);//建立5个杆,前三个为游戏杆，第四、五做为临时存储数据的杆
    }

    if(Isbegunbefore)
    {
        Init() ;//显示清空
    }


    for(int i=pegs;i>=1;i--)
    {
        poles[0].push(i);//对第一杆数据初始化
    }


    for( int i=1;i<=pegs;i++)// 显示第一杆初始塔层
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

    Isbegunbefore=true;//已设定过初始塔层
    lastdisk=pegs;//此数据用于清空上次塔层

}

void Widget::Init()
{
    for(int i=0;i<5;i++)
    {
         poles[i].clear();
    }

    for(int j=0;j<3;j++)
    {
        for(int i=1;i<=lastdisk;i++)//删除显示的塔层
        {
            delete Peg[j][i];
        }
    }

}



void Widget::move()//移动塔层的实现
{
    if(movecondition!=Victor)//如果状态非胜利，则执行移动的函数
    {
        if(isGetdisk)
        {
            movecondition=getpeg(poles, pegs);//取塔层
        }

        else
        {
            movecondition=putpeg(poles, pegs);//放塔层
        }

    }

    if(movecondition==NoDisk)
    {
        QMessageBox::information(0, tr("提示"),tr("所取杆塔层为空"));
        ui->Label1->setPixmap (QPixmap::fromImage(Imagex[1]));
        ui->Label2->setPixmap (QPixmap::fromImage(Imagex[2]));
        ui->Label3->setPixmap (QPixmap::fromImage(Imagex[3]));

        isGetdisk=false;
        ui->LabelState->setText(tr("请选取塔层"));
    }

    else if(movecondition==BadInput)
    {
        QMessageBox::information(0, tr("提示"),tr("大的塔层放在小的塔层上面是不被允许的"));

        isGetdisk=true;
        ui->LabelState->setText(tr("请放置塔层"));

    }

    else if(movecondition==Victor)//胜利，并输出移动次数，并选择重启游戏或退出
    {
        movecondition=Continue;
        timer->stop ();

        const int timepast=now.secsTo(zero);

        QString ptimepast="";


        if(timepast/3600>0)
        {
            int hour=timepast/3600;
            ptimepast+=QString::number(hour);
            ptimepast+= tr("小时 ");
        }

        if((timepast%3600)/60>0)
        {
            int minute=(timepast%3600)/60;
            ptimepast+=QString::number(minute);
            ptimepast+= tr("分钟 ");
        }


        if(((timepast%3600)%60)>0)
        {
            int second=(timepast%3600)%60;
            ptimepast+=QString::number(second);
            ptimepast+= tr("秒 ");
        }

        switch ( QMessageBox::warning( this,  tr("恭喜"),
                                              tr("你用了")  + QString::number(movestimes) + tr("个步骤完成了游戏\n限时")
                                              +QString::number(zz.secsTo(zero))+tr("秒         用时")+ptimepast,
                                              tr("再玩一遍"), tr("设定新的塔层数重新开始"),
                                              tr("退出"), 0, 2 ) )
           {
           case 0: //用户按了Play again按钮,或按了回车键

               on_start_clicked();//以当前设定的层数重新开始游戏
               break;
           case 1:
               Init();//只做清空，待用户输入新的层数
               Isbegun=false;
               Isbegunbefore=false;
               timer->~QTimer();
               ui->spinBox->selectAll();
               ui->spinBox->setFocus();
               break;
           default:// 用户按了Quit按钮,或按了Esc键
               close();
               break;
           }
    }

}

int Widget::getlength(int i)//得到当前杆塔层个数
{
    int k;
    int length=0;


    while (!poles[i].empty()) //输出当前塔层的排列 （临时取出当前杆内塔层 ）
     {

         k=poles[i].top();
         atop.push_back(k);   //

         poles[3].push(poles[i].top());
         poles[i].pop();
         length++;
     };

      while (!poles[3].empty())//放回塔层
      {
            poles[i].push(poles[3].top());// 移动塔，取出from值给to赋值
            poles[3].pop();
      };
      return length;
}

int Widget::getpeg(vector< QStack<int> > &poles, int pegs)//取塔层
{

       //判断可能出现的错误：抓取的盘不存
        if(poles[lefrom-1].empty())//抓取的盘不存在
        {
            return (NoDisk);
        }

       //无错误，则执行
        else
        {
            //数据
            poles[4].push(poles[lefrom-1].top());
            poles[lefrom-1].pop();

             //界面显示
            int n=getlength(lefrom-1);
            int m=pegs;

            for(int i=1;i<=pegs;i++)//删除当前杆显示的塔层
            {
                delete Peg[lefrom-1][i] ;
            }

            for(int i=1;i<=(m-n);i++)//空位显示
            {
                Peg[lefrom-1][i]=new QLabel;

                if(lefrom==1)
                    ui->vl->addWidget(Peg[lefrom-1][i]);
                if(lefrom==2)
                    ui->vm->addWidget(Peg[lefrom-1][i]);
                if(lefrom==3)
                    ui->vr->addWidget(Peg[lefrom-1][i]);
            }

            for(int i=1;i<=n;i++)//当前杆所有塔层显示
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


int Widget::putpeg(vector< QStack<int> > &poles, int pegs)//放塔层
{
    //判断可能出现的错误：放置不合规则
    if(!poles[leto-1].empty() && poles[leto-1].top()<poles[4].top())//释放位置违反规则
    {
         return (BadInput);
    }

    else if(poles[leto-1].empty() || poles[leto-1].top()>poles[4].top())
    {
        poles[leto-1].push(poles[4].top());// 移动塔，取出暂存值给to赋值
        poles[4].pop();// 清除暂存的值

       //界面显示

        int a=getlength(leto-1);
        int b=pegs;


        for(int i=1;i<=b;i++)//删除当前杆显示的塔层
        {
            delete Peg[leto-1][i] ;
        }


        for(int i=1;i<=(b-a);i++)//空位置显示
        {
            Peg[leto-1][i]=new QLabel;

            if(leto==1)
                ui->vl->addWidget(Peg[leto-1][i]);
            if(leto==2)
                ui->vm->addWidget(Peg[leto-1][i]);
            if(leto==3)
                ui->vr->addWidget(Peg[leto-1][i]);
        }


        for(int i=1;i<=a;i++)  //当前杆所有塔层显示
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


    //判断移动后的状态，胜利或者继续
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

    if(watched ==ui->Label1 || watched == ui->v1 )   //点击杆所在的位置或者对应图片位置
    {
        if(event->type() == QEvent::MouseButtonPress)
        {

                QMouseEvent *mouseEvent = (QMouseEvent *)event;
                if(mouseEvent->buttons() &Qt::LeftButton)
                {
                    if(!Isbegun)//判断游戏是否已设定初始塔层
                    {
                        QMessageBox::information(0, tr("提示"),tr("请先设置汉诺塔层数"));//对未初始化发出警告
                        ui->spinBox->selectAll();
                        ui->spinBox->setFocus();
                        return QDialog::eventFilter(watched,event);
                    }
                    if(!timerstart)
                    {
                         QMessageBox::information(0, tr("提示"),tr("游戏暂停中，请点击继续按钮"));//
                         return QDialog::eventFilter(watched,event);
                    }

                    if(!isGetdisk)
                    {
                        ui->LabelState->setText(tr("你获取了第一杆的顶层塔"));
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
                        ui->LabelState->setText(tr("你把塔放在了第一杆的顶端 "));
                        isGetdisk=false;
                        leto=1;
                        move();
                    }

                }

                else if(mouseEvent->buttons() &Qt::RightButton)
                {
                        ui->LabelState->setText(tr("这是第一杆"));
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
                        QMessageBox::information(0, tr("提示"),tr("请先设置汉诺塔层数"));//对未初始化发出警告
                        ui->spinBox->selectAll();
                        ui->spinBox->setFocus();
                        return QDialog::eventFilter(watched,event);
                    }

                    if(!timerstart)
                    {
                         QMessageBox::information(0, tr("提示"),tr("游戏暂停中，请点击继续按钮"));//
                         return QDialog::eventFilter(watched,event);
                    }

                    if(!isGetdisk)
                    {
                        ui->LabelState->setText(tr("你获取了第二杆的顶层塔"));
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
                        ui->LabelState->setText(tr("你把塔放在了第二杆的顶端 "));
                        isGetdisk=false;
                        leto=2;
                        move();
                    }

                }

                else if(mouseEvent->buttons() &Qt::RightButton)
                {
                        ui->LabelState->setText(tr("这是第二杆"));
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
                        QMessageBox::information(0, tr("提示"),tr("请先设置汉诺塔层数"));//对未初始化发出警告
                        ui->spinBox->selectAll();
                        ui->spinBox->setFocus();
                        return QDialog::eventFilter(watched,event);
                    }

                    if(!timerstart)
                    {
                         QMessageBox::information(0, tr("提示"),tr("游戏暂停中，请点击继续按钮"));//
                         return QDialog::eventFilter(watched,event);
                    }

                    if(!isGetdisk)
                    {
                        ui->LabelState->setText(tr("你获取了第三杆的顶层塔 "));
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
                        ui->LabelState->setText(tr("你把塔放在了第三杆的顶端 "));
                        isGetdisk=false;
                        leto=3;
                        move();
                    }

                }

                else if(mouseEvent->buttons() &Qt::RightButton)
                {
                        ui->LabelState->setText(tr("这是第三杆"));
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
        QMessageBox::information(0, tr("提示"),tr("时间到，游戏将重新开始"));//
        on_start_clicked();//以当前设定的层数重新开始游戏
        return;
    }
    now=now.addSecs (-1);
    QString strTime = now.toString("hh:mm:ss");//设置系统时间显示格式
    ui->lcdNumber->display(strTime);//在lcdNumber上显示时间
}

void Widget::dclockshow()
{
    QDateTime nowtime = QDateTime::currentDateTime();//获取系统现在的时间
    QString clock = nowtime.toString("yyyy-MM-dd hh:mm:ss");//设置系统时间显示格式
    ui->clock->setText(clock);//在标签上显示时间
}




void Widget::on_pause_clicked()
{

    if(!Isbegun)
    {
        QMessageBox::information(0, tr("提示"),tr("请先开始游戏"));//对未开始发出警告
        return ;
    }

    if(timerstart)
    {
        timer->stop ();
        ui->pause->setText(tr("继续"));
        timerstart=false;

        for(int j=0;j<3;j++)
        {
            for(int i=1;i<=lastdisk;i++)//删除显示的塔层
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
        ui->pause->setText(tr("暂停"));
        timerstart=true;
        for(int j=0;j<3;j++)
        {
            delete Peg[j][0];
        }

        for(int j=0;j<3;j++)
        {
            for(int i=1;i<=lastdisk;i++)//删除显示的塔层
            {
                Peg[j][i]->show();
            }
        }
    }

}

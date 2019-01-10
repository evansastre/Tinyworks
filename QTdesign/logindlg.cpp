#include "logindlg.h"
#include "ui_logindlg.h"
#include<qmessagebox.h>
#include <QtGui>
loginDlg::loginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDlg)
{
    ui->setupUi(this);
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);// 使输入的字符变为圆点不可见
    ui->pwdLineEdit->setFocus();
}

loginDlg::~loginDlg()
{
    delete ui;
}

void loginDlg::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void loginDlg::on_exit_clicked()
{
    close();
}

void loginDlg::on_login_clicked()
{
    static int i=1;
    if(ui->pwdLineEdit->text()==tr("100"))
    accept();//输入100则进入主界面

    else if(i!=3)
    {
        QMessageBox::warning(this,tr("提示"),tr("输入错误"),QMessageBox::tr("重新输入"));
        ui->pwdLineEdit->clear();//清除已输入的值
        ui->pwdLineEdit->setFocus();//定位在输入框
        i++;//错误计数
    }
    else
    {
       QMessageBox::warning(this,tr("提示"),tr("100 才可以"),QMessageBox::tr("想好了再进吧"));
       close();//错3次后自动关闭
    }
}

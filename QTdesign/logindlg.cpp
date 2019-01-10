#include "logindlg.h"
#include "ui_logindlg.h"
#include<qmessagebox.h>
#include <QtGui>
loginDlg::loginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDlg)
{
    ui->setupUi(this);
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);// ʹ������ַ���ΪԲ�㲻�ɼ�
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
    accept();//����100�����������

    else if(i!=3)
    {
        QMessageBox::warning(this,tr("��ʾ"),tr("�������"),QMessageBox::tr("��������"));
        ui->pwdLineEdit->clear();//����������ֵ
        ui->pwdLineEdit->setFocus();//��λ�������
        i++;//�������
    }
    else
    {
       QMessageBox::warning(this,tr("��ʾ"),tr("100 �ſ���"),QMessageBox::tr("������ٽ���"));
       close();//��3�κ��Զ��ر�
    }
}

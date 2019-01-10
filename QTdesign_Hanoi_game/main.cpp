#include <QtGui/QApplication>
#include "widget.h"
#include "logindlg.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("system"));//œ‘ æ÷–Œƒ

    Widget w;
    loginDlg login;

    if(login.exec()==QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else return 0;
}



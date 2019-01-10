#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>

namespace Ui {
    class loginDlg;
}

class loginDlg : public QDialog {
    Q_OBJECT
public:
    loginDlg(QWidget *parent = 0);
    ~loginDlg();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::loginDlg *ui;

private slots:
    void on_login_clicked();//登入，错误时警告并返回，正确时则打开游戏界面
    void on_exit_clicked();//退出

};

#endif // LOGINDLG_H

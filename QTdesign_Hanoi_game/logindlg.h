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
    void on_login_clicked();//���룬����ʱ���沢���أ���ȷʱ�����Ϸ����
    void on_exit_clicked();//�˳�

};

#endif // LOGINDLG_H

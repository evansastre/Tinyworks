/********************************************************************************
** Form generated from reading UI file 'logindlg.ui'
**
** Created: Tue Dec 27 17:21:37 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDLG_H
#define UI_LOGINDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_loginDlg
{
public:
    QPushButton *login;
    QPushButton *exit;
    QLabel *label;
    QLineEdit *pwdLineEdit;

    void setupUi(QDialog *loginDlg)
    {
        if (loginDlg->objectName().isEmpty())
            loginDlg->setObjectName(QString::fromUtf8("loginDlg"));
        loginDlg->resize(400, 300);
        loginDlg->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix2/Image/01300000207463121674194017974_s.jpg);"));
        login = new QPushButton(loginDlg);
        login->setObjectName(QString::fromUtf8("login"));
        login->setGeometry(QRect(310, 60, 75, 23));
        exit = new QPushButton(loginDlg);
        exit->setObjectName(QString::fromUtf8("exit"));
        exit->setGeometry(QRect(270, 180, 75, 23));
        label = new QLabel(loginDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 60, 81, 16));
        pwdLineEdit = new QLineEdit(loginDlg);
        pwdLineEdit->setObjectName(QString::fromUtf8("pwdLineEdit"));
        pwdLineEdit->setGeometry(QRect(170, 60, 113, 20));
        pwdLineEdit->setMaxLength(32767);

        retranslateUi(loginDlg);

        QMetaObject::connectSlotsByName(loginDlg);
    } // setupUi

    void retranslateUi(QDialog *loginDlg)
    {
        loginDlg->setWindowTitle(QApplication::translate("loginDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        login->setText(QApplication::translate("loginDlg", "\346\217\220\344\272\244", 0, QApplication::UnicodeUTF8));
        exit->setText(QApplication::translate("loginDlg", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("loginDlg", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class loginDlg: public Ui_loginDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDLG_H

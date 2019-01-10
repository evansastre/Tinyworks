/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Tue Dec 27 17:23:07 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *Illustration;
    QPushButton *start;
    QPushButton *exit;
    QLabel *arrange;
    QSpinBox *spinBox;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *pegs;
    QLabel *Label1;
    QLabel *Label2;
    QLabel *Label3;
    QLabel *LabelState;
    QGroupBox *v1;
    QVBoxLayout *vl;
    QGroupBox *v2;
    QVBoxLayout *vm;
    QGroupBox *v3;
    QVBoxLayout *vr;
    QFrame *line;
    QLCDNumber *lcdNumber;
    QPushButton *pause;
    QLabel *label;
    QLabel *clock;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->setWindowModality(Qt::WindowModal);
        Widget->resize(639, 597);
        Widget->setAutoFillBackground(true);
        Widget->setStyleSheet(QString::fromUtf8(""));
        Illustration = new QPushButton(Widget);
        Illustration->setObjectName(QString::fromUtf8("Illustration"));
        Illustration->setGeometry(QRect(10, 70, 141, 31));
        Illustration->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(85, 0, 127);"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix2/Image/t1.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Illustration->setIcon(icon);
        start = new QPushButton(Widget);
        start->setObjectName(QString::fromUtf8("start"));
        start->setGeometry(QRect(420, 30, 75, 31));
        start->setStyleSheet(QString::fromUtf8("color: rgb(85, 0, 127);\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix2/Image/t3.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        start->setIcon(icon1);
        exit = new QPushButton(Widget);
        exit->setObjectName(QString::fromUtf8("exit"));
        exit->setGeometry(QRect(520, 30, 75, 31));
        exit->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(85, 0, 127);"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix2/Image/t2.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        exit->setIcon(icon2);
        arrange = new QLabel(Widget);
        arrange->setObjectName(QString::fromUtf8("arrange"));
        arrange->setGeometry(QRect(190, 30, 71, 31));
        arrange->setStyleSheet(QString::fromUtf8("color: rgb(85, 0, 127);"));
        spinBox = new QSpinBox(Widget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(300, 30, 81, 31));
        spinBox->setCursor(QCursor(Qt::OpenHandCursor));
        spinBox->setMouseTracking(false);
        spinBox->setContextMenuPolicy(Qt::DefaultContextMenu);
        spinBox->setWrapping(false);
        spinBox->setMinimum(1);
        spinBox->setMaximum(8);
        spinBox->setValue(1);
        horizontalLayoutWidget_2 = new QWidget(Widget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(60, 410, 551, 161));
        pegs = new QHBoxLayout(horizontalLayoutWidget_2);
        pegs->setSpacing(6);
        pegs->setContentsMargins(11, 11, 11, 11);
        pegs->setObjectName(QString::fromUtf8("pegs"));
        pegs->setContentsMargins(0, 0, 0, 0);
        Label1 = new QLabel(horizontalLayoutWidget_2);
        Label1->setObjectName(QString::fromUtf8("Label1"));
        Label1->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix2/Image/s1.jpg")));

        pegs->addWidget(Label1);

        Label2 = new QLabel(horizontalLayoutWidget_2);
        Label2->setObjectName(QString::fromUtf8("Label2"));
        Label2->setCursor(QCursor(Qt::ArrowCursor));
        Label2->setMouseTracking(false);
        Label2->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix2/Image/s2.jpg")));

        pegs->addWidget(Label2);

        Label3 = new QLabel(horizontalLayoutWidget_2);
        Label3->setObjectName(QString::fromUtf8("Label3"));
        Label3->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix2/Image/s3.jpg")));

        pegs->addWidget(Label3);

        LabelState = new QLabel(Widget);
        LabelState->setObjectName(QString::fromUtf8("LabelState"));
        LabelState->setGeometry(QRect(250, 380, 201, 16));
        v1 = new QGroupBox(Widget);
        v1->setObjectName(QString::fromUtf8("v1"));
        v1->setGeometry(QRect(50, 130, 121, 221));
        v1->setStyleSheet(QString::fromUtf8(""));
        vl = new QVBoxLayout(v1);
        vl->setSpacing(6);
        vl->setContentsMargins(11, 11, 11, 11);
        vl->setObjectName(QString::fromUtf8("vl"));
        v2 = new QGroupBox(Widget);
        v2->setObjectName(QString::fromUtf8("v2"));
        v2->setGeometry(QRect(240, 130, 121, 221));
        vm = new QVBoxLayout(v2);
        vm->setSpacing(6);
        vm->setContentsMargins(11, 11, 11, 11);
        vm->setObjectName(QString::fromUtf8("vm"));
        v3 = new QGroupBox(Widget);
        v3->setObjectName(QString::fromUtf8("v3"));
        v3->setGeometry(QRect(420, 130, 121, 221));
        v3->setFlat(false);
        v3->setCheckable(false);
        vr = new QVBoxLayout(v3);
        vr->setSpacing(6);
        vr->setContentsMargins(11, 11, 11, 11);
        vr->setObjectName(QString::fromUtf8("vr"));
        line = new QFrame(Widget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(50, 110, 521, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        lcdNumber = new QLCDNumber(Widget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(280, 80, 121, 23));
        pause = new QPushButton(Widget);
        pause->setObjectName(QString::fromUtf8("pause"));
        pause->setGeometry(QRect(420, 72, 75, 31));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(200, 80, 81, 16));
        clock = new QLabel(Widget);
        clock->setObjectName(QString::fromUtf8("clock"));
        clock->setGeometry(QRect(20, 20, 161, 31));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        Illustration->setText(QApplication::translate("Widget", "\346\270\270\346\210\217\350\257\264\346\230\216", 0, QApplication::UnicodeUTF8));
        start->setText(QApplication::translate("Widget", "\345\274\200\345\247\213", 0, QApplication::UnicodeUTF8));
        exit->setText(QApplication::translate("Widget", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
        arrange->setText(QApplication::translate("Widget", " \350\256\276\345\256\232\345\261\202\346\225\260", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        Label1->setToolTip(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/new/prefix2/Image/t5.jpg\" />\350\277\231\346\230\257\347\254\254\344\270\200\346\235\206</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        Label1->setText(QString());
#ifndef QT_NO_TOOLTIP
        Label2->setToolTip(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/new/prefix2/Image/t5.jpg\" />\350\277\231\346\230\257\347\254\254\344\272\214\346\235\206</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        Label2->setText(QString());
#ifndef QT_NO_TOOLTIP
        Label3->setToolTip(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/new/prefix2/Image/t5.jpg\" />\350\277\231\346\230\257\347\254\254\344\270\211\346\235\206</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        Label3->setText(QString());
        LabelState->setText(QApplication::translate("Widget", "TextLabel", 0, QApplication::UnicodeUTF8));
        v1->setTitle(QApplication::translate("Widget", "Pole1", 0, QApplication::UnicodeUTF8));
        v2->setTitle(QApplication::translate("Widget", "Pole2", 0, QApplication::UnicodeUTF8));
        v3->setTitle(QApplication::translate("Widget", "Pole3", 0, QApplication::UnicodeUTF8));
        pause->setText(QApplication::translate("Widget", "\346\232\202\345\201\234", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Widget", "\346\270\270\346\210\217\350\256\241\346\227\266", 0, QApplication::UnicodeUTF8));
        clock->setText(QApplication::translate("Widget", "timeshow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

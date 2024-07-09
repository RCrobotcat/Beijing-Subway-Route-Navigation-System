/********************************************************************************
** Form generated from reading UI file 'main_menu.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_MENU_H
#define UI_MAIN_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainMenu
{
public:
    QWidget *centralwidget;
    QPushButton *insertOrDelete;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *startStation;
    QTextEdit *endStation;
    QCommandLinkButton *leastTransfer;
    QCommandLinkButton *shortestTime;
    QLabel *label_3;
    QSplitter *splitter;
    QLabel *title;
    QLabel *label_4;
    QMenuBar *menubar;

    void setupUi(QMainWindow *mainMenu)
    {
        if (mainMenu->objectName().isEmpty())
            mainMenu->setObjectName("mainMenu");
        mainMenu->resize(559, 535);
        mainMenu->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(mainMenu);
        centralwidget->setObjectName("centralwidget");
        insertOrDelete = new QPushButton(centralwidget);
        insertOrDelete->setObjectName("insertOrDelete");
        insertOrDelete->setGeometry(QRect(180, 80, 191, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("\344\273\277\345\256\213")});
        font.setPointSize(15);
        font.setBold(true);
        insertOrDelete->setFont(font);
        insertOrDelete->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    /*\350\203\214\346\231\257\351\242\234\350\211\262*/  \n"
"    background-color: rgb(221, 255, 212);   \n"
"    color:black;\n"
"      \n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"    \n"
"    /*\346\214\211\344\270\213\346\227\266\345\255\227\345\220\221\345\217\263\347\247\273\345\212\2504\345\203\217\347\264\240*/  \n"
"    padding-left:4px;\n"
"    /*\346\214\211\344\270\213\346\227\266\345\255\227\345\220\221\344\270\213\347\247\273\345\212\2504\345\203\217\347\264\240*/  \n"
"    padding-top:4px;\n"
"}"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 160, 131, 61));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        label->setFont(font1);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(70, 250, 131, 61));
        label_2->setFont(font1);
        startStation = new QTextEdit(centralwidget);
        startStation->setObjectName("startStation");
        startStation->setGeometry(QRect(220, 180, 241, 31));
        endStation = new QTextEdit(centralwidget);
        endStation->setObjectName("endStation");
        endStation->setGeometry(QRect(220, 270, 241, 31));
        leastTransfer = new QCommandLinkButton(centralwidget);
        leastTransfer->setObjectName("leastTransfer");
        leastTransfer->setGeometry(QRect(260, 340, 191, 51));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(18);
        font2.setBold(true);
        leastTransfer->setFont(font2);
        leastTransfer->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    /*\350\203\214\346\231\257\351\242\234\350\211\262*/  \n"
"    background-color: rgb(217, 253, 255);   \n"
"    color:black;\n"
"      \n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"    \n"
"    /*\346\214\211\344\270\213\346\227\266\345\255\227\345\220\221\345\217\263\347\247\273\345\212\2504\345\203\217\347\264\240*/  \n"
"    padding-left:4px;\n"
"    /*\346\214\211\344\270\213\346\227\266\345\255\227\345\220\221\344\270\213\347\247\273\345\212\2504\345\203\217\347\264\240*/  \n"
"    padding-top:4px;\n"
"}"));
        shortestTime = new QCommandLinkButton(centralwidget);
        shortestTime->setObjectName("shortestTime");
        shortestTime->setGeometry(QRect(260, 410, 191, 51));
        shortestTime->setFont(font2);
        shortestTime->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    /*\350\203\214\346\231\257\351\242\234\350\211\262*/  \n"
"    background-color:  rgb(217, 253, 255);   \n"
"    color:black;\n"
"      \n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"    \n"
"    /*\346\214\211\344\270\213\346\227\266\345\255\227\345\220\221\345\217\263\347\247\273\345\212\2504\345\203\217\347\264\240*/  \n"
"    padding-left:4px;\n"
"    /*\346\214\211\344\270\213\346\227\266\345\255\227\345\220\221\344\270\213\347\247\273\345\212\2504\345\203\217\347\264\240*/  \n"
"    padding-top:4px;\n"
"}"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(90, 340, 131, 61));
        label_3->setFont(font1);
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setGeometry(QRect(80, 10, 401, 55));
        splitter->setOrientation(Qt::Horizontal);
        title = new QLabel(splitter);
        title->setObjectName("title");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font3.setPointSize(30);
        title->setFont(font3);
        splitter->addWidget(title);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(60, 230, 211, 16));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        label_4->setFont(font4);
        mainMenu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainMenu);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 559, 21));
        mainMenu->setMenuBar(menubar);

        retranslateUi(mainMenu);

        QMetaObject::connectSlotsByName(mainMenu);
    } // setupUi

    void retranslateUi(QMainWindow *mainMenu)
    {
        mainMenu->setWindowTitle(QCoreApplication::translate("mainMenu", "MainWindow", nullptr));
        insertOrDelete->setText(QCoreApplication::translate("mainMenu", "\346\217\222\345\205\245/\345\210\240\351\231\244\346\237\220\346\235\241\347\272\277\350\267\257", nullptr));
        label->setText(QCoreApplication::translate("mainMenu", "\350\276\223\345\205\245\350\265\267\345\247\213\347\253\231:", nullptr));
        label_2->setText(QCoreApplication::translate("mainMenu", "\350\276\223\345\205\245\347\273\210\347\202\271\347\253\231: ", nullptr));
        leastTransfer->setText(QCoreApplication::translate("mainMenu", "\346\234\200\345\260\221\346\215\242\344\271\230\350\267\257\345\276\204", nullptr));
        shortestTime->setText(QCoreApplication::translate("mainMenu", "\346\234\200\347\237\255\346\227\266\351\227\264\350\267\257\345\276\204", nullptr));
        label_3->setText(QCoreApplication::translate("mainMenu", "\346\237\245\350\257\242\350\267\257\347\272\277: ", nullptr));
        title->setText(QCoreApplication::translate("mainMenu", "\345\214\227\344\272\254\345\234\260\351\223\201\347\272\277\350\267\257\346\237\245\350\257\242\347\263\273\347\273\237", nullptr));
        label_4->setText(QCoreApplication::translate("mainMenu", "(\350\257\267\345\213\277\350\276\223\345\205\245\344\273\273\344\275\225\347\251\272\346\240\274\346\210\226\350\200\205\346\215\242\350\241\214!)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainMenu: public Ui_mainMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_MENU_H

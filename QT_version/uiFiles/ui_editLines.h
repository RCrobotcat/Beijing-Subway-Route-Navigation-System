/********************************************************************************
** Form generated from reading UI file 'editLines.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLINES_H
#define UI_EDITLINES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_editLines
{
public:
    QWidget *centralwidget;
    QPushButton *add;
    QPushButton *delete_2;
    QLabel *label;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *editLines)
    {
        if (editLines->objectName().isEmpty())
            editLines->setObjectName("editLines");
        editLines->resize(431, 241);
        centralwidget = new QWidget(editLines);
        centralwidget->setObjectName("centralwidget");
        add = new QPushButton(centralwidget);
        add->setObjectName("add");
        add->setGeometry(QRect(30, 130, 121, 41));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        add->setFont(font);
        add->setStyleSheet(QString::fromUtf8("QPushButton\n"
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
        delete_2 = new QPushButton(centralwidget);
        delete_2->setObjectName("delete_2");
        delete_2->setGeometry(QRect(300, 130, 101, 41));
        delete_2->setFont(font);
        delete_2->setStyleSheet(QString::fromUtf8("QPushButton\n"
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
        label->setGeometry(QRect(10, 10, 361, 61));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        label->setFont(font1);
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(40, 70, 341, 31));
        editLines->setCentralWidget(centralwidget);
        menubar = new QMenuBar(editLines);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 431, 21));
        editLines->setMenuBar(menubar);
        statusbar = new QStatusBar(editLines);
        statusbar->setObjectName("statusbar");
        editLines->setStatusBar(statusbar);

        retranslateUi(editLines);

        QMetaObject::connectSlotsByName(editLines);
    } // setupUi

    void retranslateUi(QMainWindow *editLines)
    {
        editLines->setWindowTitle(QCoreApplication::translate("editLines", "MainWindow", nullptr));
        add->setText(QCoreApplication::translate("editLines", "\346\267\273\345\212\240\347\272\277\350\267\257", nullptr));
        delete_2->setText(QCoreApplication::translate("editLines", "\345\210\240\351\231\244\347\272\277\350\267\257", nullptr));
        label->setText(QCoreApplication::translate("editLines", "\350\257\267\350\276\223\345\205\245\346\202\250\346\203\263\350\246\201\346\267\273\345\212\240\346\210\226\345\210\240\351\231\244\347\232\204\345\234\260\351\223\201\347\272\277\350\267\257\347\272\277\350\267\257: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class editLines: public Ui_editLines {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLINES_H

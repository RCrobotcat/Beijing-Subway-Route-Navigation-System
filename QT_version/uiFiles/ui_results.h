/********************************************************************************
** Form generated from reading UI file 'results.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTS_H
#define UI_RESULTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_results
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *results)
    {
        if (results->objectName().isEmpty())
            results->setObjectName("results");
        results->resize(711, 490);
        QFont font;
        font.setBold(false);
        results->setFont(font);
        centralwidget = new QWidget(results);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(150, 180, 53, 15));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(0, 70, 711, 311));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        textBrowser->setFont(font1);
        results->setCentralWidget(centralwidget);
        menubar = new QMenuBar(results);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 711, 21));
        results->setMenuBar(menubar);
        statusbar = new QStatusBar(results);
        statusbar->setObjectName("statusbar");
        results->setStatusBar(statusbar);

        retranslateUi(results);

        QMetaObject::connectSlotsByName(results);
    } // setupUi

    void retranslateUi(QMainWindow *results)
    {
        results->setWindowTitle(QCoreApplication::translate("results", "MainWindow", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class results: public Ui_results {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTS_H

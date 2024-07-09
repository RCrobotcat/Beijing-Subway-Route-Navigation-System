//
// Created by 刘宇杰 on 24-4-18.
//

#include "mainMenu.h"
#include "./uiFiles/ui_main_menu.h"
#include "QComboBox"
#include "QPushButton"
#include "iostream"
#include "string"
#include "baseCodes.h"
#include "results.h"
#include "editLines.h"

using namespace Qt;
using namespace std;

mainMenu::mainMenu(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainMenu){
    ui->setupUi(this);

    baseCodes base;
    base.graphInitial();

    // 连接按钮的clicked信号到自定义的槽函数
    connect(ui->insertOrDelete, &QPushButton::clicked, this, &mainMenu::onInsertOrDeleteClicked);
    connect(ui->leastTransfer, &QPushButton::clicked, this, &mainMenu::onLeastTransferClicked);
    connect(ui->shortestTime, &QPushButton::clicked, this, &mainMenu::onShortestTimeClicked);

    // 连接输入框的textChanged信号到自定义的槽函数
    connect(ui->startStation, &QTextEdit::textChanged, this, &mainMenu::onStartStationChanged);
    connect(ui->endStation, &QTextEdit::textChanged, this, &mainMenu::onEndStationChanged);
}

mainMenu::~mainMenu() {
    delete ui;
}

void mainMenu::onInsertOrDeleteClicked() {
    // 点击插入或删除按钮时的操作
    cout << "Insert or delete button clicked!" << endl;
    editLines *edit = new editLines();
    edit->setAcceptDrops(WA_DeleteOnClose);
    edit->show();
}

void mainMenu::onLeastTransferClicked() {
    // 点击最少换乘按钮时的操作
    cout << "Least transfer button clicked!" << endl;
    baseCodes base;
    results *res = new results();
    res->setResults(base.base_code(onStartStationChanged(), onEndStationChanged(), 1));
    res->setAcceptDrops(WA_DeleteOnClose);
    res->show();
}

void mainMenu::onShortestTimeClicked() {
    // 点击最短时间按钮时的操作
    cout << "Shortest time button clicked!" << endl;
    baseCodes base;
    results *res = new results();
    res->setResults(base.base_code(onStartStationChanged(), onEndStationChanged(), 2));
    res->setAcceptDrops(WA_DeleteOnClose);
    res->show();
}

string mainMenu::onStartStationChanged() {
    // 输入起始站时的操作
//    cout << ui->startStation->toPlainText().toStdString() << endl;
    return ui->startStation->toPlainText().toStdString();
}

string mainMenu::onEndStationChanged() {
    // 输入终点站时的操作
//    cout << ui->endStation->toPlainText().toStdString() << endl;
    return ui->endStation->toPlainText().toStdString();
}

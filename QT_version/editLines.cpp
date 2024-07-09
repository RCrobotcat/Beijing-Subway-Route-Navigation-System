//
// Created by 刘宇杰 on 24-4-18.
//

#include "editLines.h"
#include "./uiFiles/ui_editLines.h"
#include "iostream"
#include "baseCodes.h"
#include "results.h"
#include "QApplication"
using namespace std;
using namespace Qt;

editLines::editLines(QWidget *parent) : QMainWindow(parent), ui(new Ui::editLines) {
    ui->setupUi(this);

    connect(ui->add, &QPushButton::clicked, this, &editLines::on_addLine_clicked);
    connect(ui->delete_2, &QPushButton::clicked, this, &editLines::on_deleteLine_clicked);
}

editLines::~editLines() {
    delete ui;
}

void editLines::on_addLine_clicked() {
    // 点击添加线路按钮时的操作
    cout << "Add line button clicked!" << endl;
    baseCodes base;
    results *res = new results();
    res->setResults(base.insert_or_delete('a', onLineNameChanged()));
    res->setAcceptDrops(WA_DeleteOnClose);
    res->show();
}

void editLines::on_deleteLine_clicked() {
    // 点击删除线路按钮时的操作
    cout << "Delete line button clicked!" << endl;
    baseCodes base;
    results *res = new results();
    res->setResults(base.insert_or_delete('d', onLineNameChanged()));
    res->setAcceptDrops(WA_DeleteOnClose);
    res->show();
}

string editLines::onLineNameChanged() {
    // 线路名输入框内容改变时的操作
    cout << "Line name changed!" << endl;
    return ui->textEdit->toPlainText().toStdString();
}
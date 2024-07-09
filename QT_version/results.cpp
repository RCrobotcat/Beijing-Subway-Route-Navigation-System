//
// Created by 刘宇杰 on 24-4-18.
//

#include "results.h"

results::results(QWidget *parent) : QMainWindow(parent), ui(new Ui::results) {
    ui->setupUi(this);
}

results::~results() {
    delete ui;
}

void results::setResults(std::string results) {
    ui->textBrowser->setText(QString::fromStdString(results));
}
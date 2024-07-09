//
// Created by 刘宇杰 on 24-4-18.
//

#ifndef PK_SUBWAY_RESULTS_H
#define PK_SUBWAY_RESULTS_H

#include "iostream"
#include "string"
#include "QTextEdit"
#include "./uiFiles/ui_results.h"
#include "QMainWindow"

QT_BEGIN_NAMESPACE
namespace Ui { class results; }
QT_END_NAMESPACE

class results : public QMainWindow {
Q_OBJECT

public:
    explicit results(QWidget *parent = nullptr);

    ~results() override;

    void setResults(std::string results);
private:
    Ui::results *ui;
};

#endif //PK_SUBWAY_RESULTS_H

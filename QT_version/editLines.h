//
// Created by 刘宇杰 on 24-4-18.
//

#ifndef PK_SUBWAY_EDITLINES_H
#define PK_SUBWAY_EDITLINES_H

#include "QMainWindow"

QT_BEGIN_NAMESPACE
namespace Ui { class editLines; }
QT_END_NAMESPACE

class editLines : public QMainWindow {
    Q_OBJECT

public:
    explicit editLines(QWidget *parent = nullptr);

    ~editLines() override;

private slots:
    void on_addLine_clicked();
    void on_deleteLine_clicked();
    std::string onLineNameChanged();
private:
    Ui::editLines *ui;
};


#endif //PK_SUBWAY_EDITLINES_H

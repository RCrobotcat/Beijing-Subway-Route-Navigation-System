//
// Created by 刘宇杰 on 24-4-18.
//

#ifndef PK_SUBWAY_MAINMENU_H
#define PK_SUBWAY_MAINMENU_H

#include "QMainWindow"

QT_BEGIN_NAMESPACE
namespace Ui { class mainMenu; }
QT_END_NAMESPACE

class mainMenu : public QMainWindow {
    Q_OBJECT

public:
    explicit mainMenu(QWidget *parent = nullptr);

    ~mainMenu() override;

private slots:
    void onInsertOrDeleteClicked();
    void onLeastTransferClicked();
    void onShortestTimeClicked();
    std::string onStartStationChanged();
    std::string onEndStationChanged();
private:
    Ui::mainMenu *ui;
};


#endif //PK_SUBWAY_MAINMENU_H

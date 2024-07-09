#include <QApplication>
#include "mainMenu.h"

int main(int argc, char *argv[]) {
    QApplication::addLibraryPath("C:/Qt/6.6.2/mingw_64/plugins");
    QApplication a(argc, argv);
    mainMenu w;
    w.show();

    return QApplication::exec();
}

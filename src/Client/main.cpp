#include "mainwindow.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Tiny Messenger");
    w.setWindowIcon(QIcon(":/assets/icon.png"));
    w.show();

    a.connect(&a, &QApplication::aboutToQuit, &w, [&w]() {
        w.isClosedManually = true;
    });

    return a.exec();
}

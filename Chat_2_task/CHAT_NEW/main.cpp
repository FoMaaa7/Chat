#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Chat1 w;
    w.setGeometry(50,50,710,280);
    w.setWindowTitle("Chat");
    w.show();
    return a.exec();
}

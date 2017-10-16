#include <iostream>
#include <QApplication>
#include "ClientMaster.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    ClientMaster* master = new ClientMaster(10020, "224.5.23.2", YELLOW);
    master->show();
    app.exec();
}

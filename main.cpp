#include <QApplication>
#include <iostream>
#include "player.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Player p;
    return a.exec();
}

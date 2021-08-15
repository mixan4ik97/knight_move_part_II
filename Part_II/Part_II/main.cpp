#include "deskgui.h"
#include "knightmovecalculator.h"
#include <QThread>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DeskGUI w;
    KnightMoveCalculator kmc;
    QThread calcul_thread;
    kmc.moveToThread(&calcul_thread);
    calcul_thread.start();
    w.show();

    return a.exec();
}

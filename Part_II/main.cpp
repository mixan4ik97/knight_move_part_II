#include "deskgui.h"
#include "knightmovecalculator.h"
#include "movecalcul.h"
#include <QThread>
#include <QObject>
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    DeskGUI dg;
    KnightMoveCalculator kmc;
    QThread calcul_thread;
    kmc.moveToThread(&calcul_thread);
    MoveCalcul *mc[8];
    QThread t_mc[8];
    for(uint8_t i =0;i<8;i++)
        mc[i] = new MoveCalcul(i);
    QObject::connect(&dg,SIGNAL(startCalcul(uint8_t,uint8_t)),&kmc,SLOT(startCalcul(uint8_t,uint8_t)));
    QObject::connect(&dg,SIGNAL(stopCalcul()),&kmc,SLOT(stopCalcul()));
    QObject::connect(&kmc,SIGNAL(finish(QVector<uint8_t>)),&dg,SLOT(finish(QVector<uint8_t> )));
    for(uint8_t i =0;i<8;i++){
      QObject::connect(&kmc,SIGNAL(startAll(uint8_t , uint8_t )),mc[i],SLOT(startCalcul(uint8_t , uint8_t )));
      QObject::connect(&kmc,SIGNAL(stopAll()),mc[i],SLOT(stopCalcul()));
      QObject::connect(mc[i],SIGNAL(finishCalc(unsigned char , unsigned char )),&kmc,SLOT(finishCalcul(unsigned char , unsigned char )),Qt::QueuedConnection);
    }

    for(uint8_t i =0;i<8;i++)
        mc[i]->moveToThread(&t_mc[i]);
    for(uint8_t i =0;i<8;i++)
        t_mc[i].start();
    calcul_thread.start();
    dg.show();

    return a.exec();
}

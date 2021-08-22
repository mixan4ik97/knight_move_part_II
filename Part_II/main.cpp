#include <QThread>
#include <QObject>
#include <QApplication>
#include "deskgui.h"
#include "knightmovecalculator.h"
#include "movecalcul.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<uint8_t>("uint8_t");
    qRegisterMetaType<uint64_t>("uint64_t");
    QApplication a(argc, argv);
    DeskGUI dg;
    KnightMoveCalculator kmc;
    MoveCalcul *mc[8];
    QThread t_mc[8];
    for(uint8_t i =0;i<8;i++){
        mc[i] = new MoveCalcul(i);
    }
    QObject::connect(&dg,SIGNAL(startCalcul(uint8_t,uint8_t)),&kmc,SLOT(startCalcul(uint8_t,uint8_t)));
    QObject::connect(&dg,SIGNAL(stopCalcul()),&kmc,SLOT(stopCalcul()));
    QObject::connect(&kmc,SIGNAL(calculOut(QByteArray)),&dg,SLOT(calculOut(QByteArray)));
    for(uint8_t i =0;i<8;i++){
      QObject::connect(&kmc,SIGNAL(startAll(uint8_t , uint8_t )),mc[i],SLOT(startCalcul(uint8_t , uint8_t )));
      QObject::connect(&kmc,SIGNAL(stopAll()),mc[i],SLOT(stopCalcul()));
      QObject::connect(mc[i],SIGNAL(finishCalc(uint64_t , unsigned char  )),&kmc,SLOT(finishCalcul(uint64_t , unsigned char  )),Qt::UniqueConnection);
    }

    for(uint8_t i =0;i<8;i++)
        mc[i]->moveToThread(&t_mc[i]);
    for(uint8_t i =0;i<8;i++)
        t_mc[i].start();
    QObject::connect(&dg,SIGNAL(exit()),&a,SLOT(quit()));
    dg.show();
    int ret = a.exec();

    for(uint8_t i =0;i<8;i++){
        t_mc[i].quit();
        t_mc[i].wait();
    }
    for(uint8_t i =0;i<8;i++)
        delete mc[i];
    return ret;
}
